#! /usr/bin/env python3

import argparse
import datetime
import os
import pathlib
import re
import sys

import jinja2

def trim_pv(pv):
    """
    Strip anything after +git from the PV
    """
    return "".join(pv.partition("+git")[:2])

def needs_update(version, upstream):
    """
    Do a dumb comparison to determine if the version needs to be updated.
    """
    if "+git" in version:
        # strip +git and see if this is a post-release snapshot
        version = version.replace("+git", "")
    return version != upstream

def layer_path(layername, d):
    """
    Return the path to the specified layer, or None if the layer isn't present.
    """
    import re
    bbpath = d.getVar("BBPATH").split(":")
    pattern = d.getVar('BBFILE_PATTERN_' + layername)
    for path in reversed(sorted(bbpath)):
        if re.match(pattern, path + "/"):
            return path
    return None

def extract_patch_info(src_uri, d):
    """
    Parse the specified patch entry from a SRC_URI and return (base name, layer name, status) tuple
    """
    import bb.fetch, bb.utils

    info = {}
    localpath = bb.fetch.decodeurl(src_uri)[2]
    info["name"] = os.path.basename(localpath)
    info["layer"] = bb.utils.get_file_layer(localpath, d)

    status = "Unknown"
    with open(localpath, errors="ignore") as f:
        m = re.search(r"^[\t ]*Upstream[-_ ]Status:?[\t ]*(\w*)", f.read(), re.IGNORECASE | re.MULTILINE)
        if m:
            # TODO: validate
            status = m.group(1)
    info["status"] = status
    return info

def harvest_data(machines, recipes):
    import bb.tinfoil
    with bb.tinfoil.Tinfoil() as tinfoil:
        tinfoil.prepare(config_only=True)
        corepath = layer_path("core", tinfoil.config_data)
        sys.path.append(os.path.join(corepath, "lib"))
    import oe.recipeutils
    import oe.patch

    # Queue of recipes that we're still looking for upstream releases for
    to_check = list(recipes)

    # Upstream releases
    upstreams = {}
    # Machines to recipes to versions
    versions = {}

    for machine in machines:
        print(f"Gathering data for {machine}...")
        os.environ["MACHINE"] = machine
        with bb.tinfoil.Tinfoil() as tinfoil:
            versions[machine] = {}

            tinfoil.prepare(quiet=2)
            for recipe in recipes:
                try:
                    d = tinfoil.parse_recipe(recipe)
                except bb.providers.NoProvider:
                    continue

                if recipe in to_check:
                    try:
                        info = oe.recipeutils.get_recipe_upstream_version(d)
                        upstreams[recipe] = info["version"]
                        to_check.remove(recipe)
                    except (bb.providers.NoProvider, KeyError):
                        pass

                details = versions[machine][recipe] = {}
                details["recipe"] = d.getVar("PN")
                details["version"] = trim_pv(d.getVar("PV"))
                details["fullversion"] = d.getVar("PV")
                details["patches"] = [extract_patch_info(p, d) for p in oe.patch.src_patches(d)]
                details["patched"] = bool(details["patches"])

    # Now backfill the upstream versions
    for machine in versions:
        for recipe in versions[machine]:
            data = versions[machine][recipe]
            data["upstream"] = upstreams[recipe]
            data["needs_update"] = needs_update(data["version"], data["upstream"])
    return upstreams, versions

# TODO can this be inferred from the list of recipes in the layer
recipes = ("virtual/kernel",
           "scp-firmware",
           "trusted-firmware-a",
           "trusted-firmware-m",
           "edk2-firmware",
           "u-boot",
           "optee-os",
           "armcompiler-native",
           "gcc-aarch64-none-elf-native",
           "gcc-arm-none-eabi-native")


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

    def render(self, context, output: pathlib.Path):
        # Default implementation for convenience
        with open(output, "wt") as f:
            f.write(self.get_template(f"machine-summary-{self.name}.jinja").render(context))

    def get_template(self, name):
        template_dir = os.path.dirname(os.path.abspath(__file__))
        env = jinja2.Environment(
            loader=jinja2.FileSystemLoader(template_dir),
            autoescape=jinja2.select_autoescape(),
            trim_blocks=True,
            lstrip_blocks=True
        )
        def is_old(version, upstream):
            if "+git" in version:
                # strip +git and see if this is a post-release snapshot
                version = version.replace("+git", "")
            return version != upstream
        env.tests["old"] = is_old

        return env.get_template(name)

class TextOverview(Format):
    name = "overview.txt"

class HtmlUpdates(Format):
    name = "updates.html"

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="machine-summary")
    parser.add_argument("machines", nargs="+", help="machine names", metavar="MACHINE")
    parser.add_argument("-t", "--type", required=True, choices=Format.registry.keys())
    parser.add_argument("-o", "--output", type=pathlib.Path, required=True)
    args = parser.parse_args()

    context = {}
    # TODO: include git describe for meta-arm
    context["timestamp"] = str(datetime.datetime.now().strftime("%c"))
    context["recipes"] = sorted(recipes)
    context["releases"], context["data"] = harvest_data(args.machines, recipes)

    formatter = Format.get_format(args.type)
    formatter.render(context, args.output)
