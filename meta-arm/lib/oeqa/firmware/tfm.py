# SPDX-License-Identifier: MIT
"""Run the TF-M regression firmware and check its serial results."""

import os
from pathlib import Path
import re
import select
import shlex
import subprocess
import time
from types import SimpleNamespace
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
        errors.append("TF-M did not finish before the model exited or timed out")
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
    if args.qemu and (not args.qemu_options or not args.boot_address):
        raise RuntimeError("QEMU needs QB_MACHINE and a boot address")
    for address in ((args.boot_address, args.image_address) if args.qemu
                    else (args.image_address,)):
        try:
            int(address, 0)
        except ValueError as error:
            raise RuntimeError(f"Invalid load address: {address}") from error
    for path in (args.qemu or args.fvp, args.bootloader, args.image):
        if not Path(path).is_file():
            raise RuntimeError(f"Missing test input: {path}")

    if args.qemu:
        command = [
            args.qemu, *args.qemu_options, "-nographic", "-monitor", "none",
            "-no-reboot",
            "-device", f"loader,file={args.bootloader},addr={args.boot_address},force-raw=on",
            "-device", f"loader,file={args.image},addr={args.image_address},force-raw=on",
        ]
        env = None
    else:
        command = [
            args.fvp, "--quiet",
            "-C", "mps3_board.uart0.out_file=-",
            "-C", "mps3_board.uart0.unbuffered_output=1",
            "-C", "mps3_board.telnetterminal0.start_telnet=0",
            "-C", "mps3_board.visualisation.disable-visualisation=1",
            "-a", f"cpu0*={args.bootloader}",
            "--data", f"{args.image}@{args.image_address}",
        ]
        env = os.environ.copy()
        fvp_lib = Path(args.fvp).resolve().parents[2] / "python/lib"
        env["LD_LIBRARY_PATH"] = os.pathsep.join(
            filter(None, (str(fvp_lib), env.get("LD_LIBRARY_PATH")))
        )
    deadline = time.monotonic() + args.timeout
    output = bytearray()
    complete = False
    process = subprocess.Popen(command, stdin=subprocess.DEVNULL,
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               env=env)
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


def testimage_main(d):
    import bb

    fvp = d.getVar("TFM_TEST_FVP")
    bindir = Path(d.getVar("STAGING_BINDIR_NATIVE"))
    build = Path(d.getVar("B"))
    test_log_dir = Path(d.getVar("TEST_LOG_DIR"))
    results = test_log_dir / "results.log"
    test_log_dir.mkdir(parents=True, exist_ok=True)
    results.write_text("", encoding="utf-8")

    qemu_name = d.getVar("QB_SYSTEM_NAME") if not fvp else None
    qemu_machine = d.getVar("QB_MACHINE") if not fvp else None
    if not fvp and (not qemu_name or not qemu_machine):
        bb.fatal("testimage: QB_SYSTEM_NAME and QB_MACHINE must be set")
    qemu_options = [] if fvp else shlex.split(" ".join(
        d.getVar(name) or "" for name in (
            "QB_MACHINE", "QB_CPU", "QB_SMP", "QB_MEM", "QB_OPT_APPEND",
        )
    ))

    config = SimpleNamespace(
        qemu=None if fvp else str(bindir / qemu_name),
        fvp=str(bindir / fvp) if fvp else None,
        qemu_options=qemu_options,
        bootloader=str(build / "bin" / ("bl2.axf" if fvp else "bl2.bin")),
        boot_address=None if fvp else d.getVar("TFM_TEST_BL2_ADDR"),
        image=str(Path(d.getVar("TFM_NS_TEST_B")) / "bin" /
                  "tfm_s_ns_signed.bin"),
        image_address=d.getVar("TFM_TEST_IMAGE_ADDR"),
        log=str(test_log_dir / ("fvp.log" if fvp else "qemu.log")),
        results=str(results),
        junit=str(Path(d.getVar("LOG_DIR")) / "oeqa" / "junit.xml"),
        timeout=int(d.getVar("TFM_TEST_TIMEOUT")),
    )
    failure = None
    try:
        run(config)
    except RuntimeError as error:
        failure = error

    for line in results.read_text(encoding="utf-8").splitlines():
        bb.plain(line)
    if failure:
        bb.fatal(f"testimage: {failure}")
