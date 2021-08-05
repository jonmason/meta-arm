#! /usr/bin/env python3

import argparse
import pathlib
import re
import subprocess
import sys

import yaml

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("config", type=argparse.FileType())
    parser.add_argument("metaarm", type=pathlib.Path, help="Path to meta-arm")
    parser.add_argument("others", type=pathlib.Path, help="Path to parent of dependencies")
    args = parser.parse_args()

    config = yaml.safe_load(args.config)
    layers = config["layers"]
    dependencies = config["dependencies"]

    found_layers = [p for p in args.metaarm.glob("meta-*") if p.is_dir()]
    print(f"Testing {len(layers)} layers: {', '.join(layers)}.")
    print(f"Found {len(found_layers)} layers in meta-arm.")
    print()

    cli = ["yocto-check-layer-wrapper",]
    cli.extend([args.metaarm / layer for layer in layers])
    cli.append("--dependency")
    cli.extend([args.others / layer for layer in dependencies])
    cli.append("--no-auto-dependency")

    passed = 0
    process = subprocess.Popen(cli, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    while True:
        line = process.stdout.readline()
        if process.poll() is not None:
            break
        print(line.strip())
        if re.search(r"meta-.+ PASS", line):
            passed += 1

    print(f"Coverage: {int(passed / len(found_layers) * 100)}%")
    sys.exit(process.returncode)
