#! /usr/bin/env python3

import argparse
import datetime
import os
import pathlib
import re
import sys
from typing import Optional


def trim_pv(pv):
    """
    Strip anything after +git from the PV
    """
    return "".join(pv.partition("+git")[:2])

def needs_update(version, upstream):
    """Report an upgrade only when upstream is newer than the recipe."""
    import bb.utils

    if not upstream:
        return False
    if upstream.endswith("-new-commits-available"):
        return True
    return bb.utils.vercmp_string(version, upstream) < 0

def safe_patches(patches):
    for info in patches:
        if info["status"] in ("Denied", "Pending", "Unknown"):
            return False
    return True

def layer_path(layername: str, d) -> pathlib.Path:
    """
    Return the path to the specified layer, or None if the layer isn't present.
    """
    if not hasattr(layer_path, "cache"):
        # Don't use functools.lru_cache as we don't want d changing to invalidate the cache
        layer_path.cache = {}

    if layername in layer_path.cache:
        return layer_path.cache[layername]

    bbpath = d.getVar("BBPATH").split(":")
    pattern = d.getVar('BBFILE_PATTERN_' + layername)
    for path in reversed(sorted(bbpath)):
        if re.match(pattern, path + "/"):
            layer_path.cache[layername] = pathlib.Path(path)
            return layer_path.cache[layername]
    return None

def get_url_for_patch(layer: str, localpath: pathlib.Path, d) -> str:
    root = layer_path(layer, d)
    if root is None or not localpath.is_relative_to(root):
        return None
    relative = localpath.relative_to(root)

    # TODO: use layerindexlib
    # TODO: assumes default branch
    if layer == "core":
        return f"https://git.openembedded.org/openembedded-core/tree/meta/{relative}"
    elif layer in ("meta-arm", "meta-arm-bsp", "arm-toolchain"):
        directory = "meta-arm-toolchain" if layer == "arm-toolchain" else layer
        return f"https://git.yoctoproject.org/meta-arm/tree/{directory}/{relative}"
    else:
        print(f"WARNING: Don't know web URL for layer {layer}", file=sys.stderr)
        return None

def extract_patch_info(src_uri, d):
    """
    Parse the specified patch entry from a SRC_URI and return (base name, layer name, status) tuple
    """
    import bb.fetch, bb.utils

    info = {}
    localpath = pathlib.Path(bb.fetch.decodeurl(src_uri)[2])
    info["name"] = localpath.name
    info["layer"] = bb.utils.get_file_layer(str(localpath), d)
    info["url"] = get_url_for_patch(info["layer"], localpath, d)

    status = "Unknown"
    with open(localpath, errors="ignore") as f:
        m = re.search(r"^[\t ]*Upstream[-_ ]Status:?[\t ]*(\w*)", f.read(), re.IGNORECASE | re.MULTILINE)
        if m:
            # TODO: validate
            status = m.group(1)
    info["status"] = status
    return info

def layer_dirs():
    """Find this checkout's BitBake layers without a hard-coded layer list."""
    root = pathlib.Path(__file__).resolve().parent.parent
    return sorted(path for path in root.glob("meta-*")
                  if (path / "conf" / "layer.conf").is_file())


def all_machines(layers):
    return sorted({path.stem for layer in layers
                   for path in layer.glob("conf/machine/*.conf")})


def recipe_name(path):
    # BitBake recipe and append filenames are PN_VERSION.bb[append].
    return path.stem.rsplit("_", 1)[0].rstrip("%") if "_" in path.stem else path.stem.rstrip("%")


def all_recipes(layers):
    names = {recipe_name(path) for layer in layers
             for pattern in ("recipes-*/*/*.bb", "recipes-*/*/*.bbappend")
             for path in layer.glob(pattern)}
    # Report the active providers as well as named kernel/bootloader recipes.
    names.update(("virtual/kernel", "virtual/bootloader"))
    return sorted(names)


def upstream_key(d):
    """Cache checks only when the source and update policy are identical."""
    fields = ("PN", "PV", "SRC_URI", "SRCREV", "UPSTREAM_CHECK_COMMITS",
              "UPSTREAM_CHECK_URI", "UPSTREAM_CHECK_REGEX",
              "UPSTREAM_CHECK_GITTAGREGEX", "RECIPE_UPSTREAM_VERSION")
    return tuple(d.getVar(field) for field in fields)


def harvest_data(machines, recipes):
    import bb.fetch
    import bb.tinfoil
    with bb.tinfoil.Tinfoil() as tinfoil:
        tinfoil.prepare(config_only=True)
        corepath = layer_path("core", tinfoil.config_data)
        sys.path.append(os.path.join(corepath, "lib"))
    import oe.recipeutils
    import oe.patch

    upstream_cache = {}
    # Machines to recipes to versions
    versions = {}

    for machine in machines:
        print(f"Gathering data for {machine}...", file=sys.stderr)
        os.environ["MACHINE"] = machine
        with bb.tinfoil.Tinfoil() as tinfoil:
            versions[machine] = {}

            tinfoil.prepare(quiet=2)
            for recipe in recipes:
                try:
                    recipe_file = tinfoil.get_recipe_file(recipe)
                except bb.providers.NoProvider:
                    continue
                d = tinfoil.parse_recipe_file(recipe_file)

                key = upstream_key(d)
                if key not in upstream_cache:
                    try:
                        upstream_cache[key] = oe.recipeutils.get_recipe_upstream_version(d)
                    except (bb.fetch.FetchError, bb.fetch.NoMethodError, KeyError) as exc:
                        print(f"Cannot check upstream version of {recipe}: {exc}", file=sys.stderr)
                        upstream_cache[key] = {}
                info = upstream_cache[key]
                upstream = info.get("version") or None

                details = versions[machine][recipe] = {}
                details["recipe"] = d.getVar("PN")
                details["version"] = trim_pv(d.getVar("PV"))
                details["fullversion"] = d.getVar("PV")
                details["upstream"] = upstream
                details["needs_update"] = needs_update(
                    info.get("current_version", d.getVar("PV")), upstream)
                details["appends"] = [str(pathlib.Path(path))
                                      for path in tinfoil.get_file_appends(recipe_file)]
                details["patches"] = [extract_patch_info(p, d) for p in oe.patch.src_patches(d)]
                details["patched"] = bool(details["patches"])
                details["patches_safe"] = safe_patches(details["patches"])

    return versions


class Format:
    """
    The name of this format
    """
    name = None
    """
    Registry of names to classes
    """
    registry = {}

    def __init_subclass__(cls, **kwargs):
        super().__init_subclass__(**kwargs)
        assert cls.name
        cls.registry[cls.name] = cls

    @classmethod
    def get_format(cls, name):
        return cls.registry[name]()

    def render(self, context, output: Optional[pathlib.Path]):
        pass

    def get_template(self, name):
        import jinja2

        template_dir = os.path.dirname(os.path.abspath(__file__))
        env = jinja2.Environment(
            loader=jinja2.FileSystemLoader(template_dir),
            extensions=['jinja2.ext.i18n'],
            autoescape=jinja2.select_autoescape(),
            trim_blocks=True,
            lstrip_blocks=True
        )

        # We only need i18n for plurals
        env.install_null_translations()

        return env.get_template(name)

class TextOverview(Format):
    name = "overview.txt"

    def render(self, context, output: Optional[pathlib.Path]):
        summary = self.get_template("machine-summary-overview.txt.jinja").render(context)
        if output is None:
            sys.stdout.write(summary)
        else:
            output.write_text(summary, encoding="utf-8")

class HtmlUpdates(Format):
    name = "report"

    def render(self, context, output: pathlib.Path):
        if output.exists() and not output.is_dir():
            print(f"{output} is not a directory", file=sys.stderr)
            sys.exit(1)

        if not output.exists():
            output.mkdir(parents=True)

        with open(output / "index.html", "wt") as f:
            f.write(self.get_template(f"report-index.html.jinja").render(context))

        subcontext = context.copy()
        del subcontext["data"]
        for machine, subdata in context["data"].items():
            subcontext["machine"] = machine
            subcontext["data"] = subdata
            with open(output / f"{machine}.html", "wt") as f:
                f.write(self.get_template(f"report-details.html.jinja").render(subcontext))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Summarize machine recipes in an initialized BitBake environment.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""Examples:
  scripts/machine-summary.py --all-machines
  scripts/machine-summary.py rdv2
  scripts/machine-summary.py --all-machines -t report -o update-report""")
    parser.add_argument("machines", nargs="*", help="machine names", metavar="MACHINE")
    parser.add_argument("--all-machines", action="store_true",
                        help="include every machine in this checkout")
    parser.add_argument("-t", "--type", default="overview.txt",
                        choices=Format.registry.keys(), help="output format (default: overview.txt)")
    parser.add_argument("-o", "--output", type=pathlib.Path,
                        help="output file, or directory for report (default: stdout for overview.txt)")
    args = parser.parse_args()
    if args.type == "report" and args.output is None:
        parser.error("--output is required for report")
    if not args.machines and not args.all_machines:
        parser.error("specify a machine or --all-machines")

    layers = layer_dirs()
    machines = sorted(set(args.machines) | set(all_machines(layers) if args.all_machines else []))
    if not machines:
        parser.error("no machines found")
    recipes = all_recipes(layers)
    context = {}
    # TODO: include git describe for meta-arm
    context["timestamp"] = str(datetime.datetime.now().strftime("%c"))
    context["recipes"] = sorted(recipes)
    context["data"] = harvest_data(machines, recipes)

    formatter = Format.get_format(args.type)
    formatter.render(context, args.output)
