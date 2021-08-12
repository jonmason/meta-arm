#! /usr/bin/env python3

import os
import sys
import argparse
import datetime

import jinja2

def get_template(name):
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

    return env.get_template(f"machine-summary-{name}.jinja")

def trim_pv(pv):
    """
    Strip anything after +git from the PV
    """
    return "".join(pv.partition("+git")[:2])

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

def harvest_data(machines, recipes):
    import bb.tinfoil, bb.utils
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
                details["patched"] = bool(oe.patch.src_patches(d))

    # Now backfill the upstream versions
    for machine in versions:
        for recipe in versions[machine]:
            versions[machine][recipe]["upstream"] = upstreams[recipe]

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

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="machine-summary")
    parser.add_argument("machines", nargs="+", help="machine names", metavar="MACHINE")
    parser.add_argument("-t", "--template", required=True)
    parser.add_argument("-o", "--output", required=True, type=argparse.FileType('w', encoding='UTF-8'))
    args = parser.parse_args()

    template = get_template(args.template)

    context = {}
    # TODO: include git describe for meta-arm
    context["timestamp"] = str(datetime.datetime.now().strftime("%c"))
    context["recipes"] = sorted(recipes)
    context["releases"], context["data"] = harvest_data(args.machines, recipes)

    args.output.write(template.render(context))
