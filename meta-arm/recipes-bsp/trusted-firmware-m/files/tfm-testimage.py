#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
"""Run the TF-M regression firmware in QEMU and check its serial results."""

import argparse
import os
from pathlib import Path
import re
import select
import subprocess
import time
import xml.etree.ElementTree as ET


def check_results(output, complete=True):
    output = re.sub(r"\x1b\[[0-9;]*m", "", output.decode("utf-8", "replace"))
    cases = []
    suite = "TF-M"
    for line in output.splitlines():
        match = re.search(r"Running Test Suite (.*?)\.\.\.", line)
        if match:
            suite = match.group(1)
        match = re.search(r"\bTEST: (.*?) - (PASSED|FAILED|SKIPPED)!", line)
        if match:
            cases.append((suite, match.group(1), match.group(2)))

    errors = []
    if not complete:
        errors.append("TF-M did not finish before QEMU exited or timed out")
    if re.search(r"TESTSUITE FAILED!|Test suite .* has FAILED", output) and not any(
        result == "FAILED" for _, _, result in cases
    ):
        errors.append("TF-M reported a failed test suite")
    for area in ("Secure", "Non-secure"):
        marker = f"*** End of {area} test suites ***"
        if marker not in output:
            errors.append(f"TF-M did not finish the {area} test suites")
    if not any(result in ("PASSED", "FAILED") for _, _, result in cases):
        errors.append("TF-M did not report any passing tests")
    return cases, errors


def write_junit(path, cases, errors):
    failures = sum(result == "FAILED" for _, _, result in cases) + len(errors)
    suite = ET.Element("testsuite", name="TF-M regression tests",
                       tests=str(len(cases) + len(errors)),
                       failures=str(failures),
                       skipped=str(sum(result == "SKIPPED" for _, _, result in cases)))
    for group, name, result in cases:
        case = ET.SubElement(suite, "testcase", classname=group, name=name)
        if result == "FAILED":
            ET.SubElement(case, "failure", message="TF-M test failed")
        elif result == "SKIPPED":
            ET.SubElement(case, "skipped")
    for index, error in enumerate(errors, 1):
        case = ET.SubElement(suite, "testcase", classname="TF-M runner",
                             name=f"completion {index}")
        ET.SubElement(case, "failure", message=error)
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    ET.ElementTree(suite).write(path, encoding="utf-8", xml_declaration=True)


def run(args):
    for address in (args.boot_address, args.image_address):
        try:
            int(address, 0)
        except ValueError as error:
            raise RuntimeError(f"Invalid QEMU load address: {address}") from error
    for path in (args.qemu, args.bootloader, args.image):
        if not Path(path).is_file():
            raise RuntimeError(f"Missing test input: {path}")

    command = [
        args.qemu, "-M", args.machine, "-display", "none", "-monitor", "none",
        "-serial", "stdio", "-no-reboot",
        "-device", f"loader,file={args.bootloader},addr={args.boot_address},force-raw=on",
        "-device", f"loader,file={args.image},addr={args.image_address},force-raw=on",
    ]
    deadline = time.monotonic() + args.timeout
    output = bytearray()
    complete = False
    process = subprocess.Popen(command, stdin=subprocess.DEVNULL,
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    try:
        while time.monotonic() < deadline:
            ready, _, _ = select.select([process.stdout], [], [], max(0, min(1, deadline - time.monotonic())))
            if ready:
                chunk = os.read(process.stdout.fileno(), 65536)
                if chunk:
                    output.extend(chunk)
                    if b"\x04" in chunk:
                        complete = True
                        break
                elif process.poll() is not None:
                    break
            elif process.poll() is not None:
                break
    finally:
        if process.poll() is None:
            process.terminate()
        try:
            tail, _ = process.communicate(timeout=5)
            output.extend(tail)
        except subprocess.TimeoutExpired:
            process.kill()
            tail, _ = process.communicate()
            output.extend(tail)
        Path(args.log).parent.mkdir(parents=True, exist_ok=True)
        Path(args.log).write_bytes(output)

    cases, errors = check_results(output, complete)
    write_junit(args.junit, cases, errors)
    lines = [f"RESULTS - {suite}.{name}: {result}" for suite, name, result in cases]
    lines.extend(f"RESULTS - TF-M runner: FAILED ({error})" for error in errors)
    passed = sum(result == "PASSED" for _, _, result in cases)
    skipped = sum(result == "SKIPPED" for _, _, result in cases)
    failed = sum(result == "FAILED" for _, _, result in cases) + len(errors)
    lines.append(f"SUMMARY: TF-M regression tests: {passed} passed, "
                 f"{skipped} skipped, {failed} failed; serial log: {args.log}")
    Path(args.results).write_text("\n".join(lines) + "\n", encoding="utf-8")
    if failed:
        raise RuntimeError(f"TF-M regression tests failed; see {args.log}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--qemu", required=True)
    parser.add_argument("--machine", required=True)
    parser.add_argument("--bootloader", required=True)
    parser.add_argument("--boot-address", required=True)
    parser.add_argument("--image", required=True)
    parser.add_argument("--image-address", required=True)
    parser.add_argument("--log", required=True)
    parser.add_argument("--results", required=True)
    parser.add_argument("--junit", required=True)
    parser.add_argument("--timeout", type=int, default=300)
    try:
        run(parser.parse_args())
    except RuntimeError as error:
        parser.exit(1, f"testimage: {error}\n")
