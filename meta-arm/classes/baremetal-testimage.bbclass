# Run a bare-metal image under QEMU and check its serial output.
inherit testimage

TESTIMAGEDEPENDS = ""
do_testimage[depends] += "qemu-system-native:do_populate_sysroot"

python do_testimage() {
    import os
    import shlex
    import subprocess

    expected = d.getVar("TESTIMAGE_EXPECTED_OUTPUT")
    if not expected:
        bb.fatal("TESTIMAGE_EXPECTED_OUTPUT must be set")

    qemu = os.path.join(d.getVar("STAGING_BINDIR_NATIVE"), d.getVar("QB_SYSTEM_NAME"))
    image = os.path.join(d.getVar("DEPLOY_DIR_IMAGE"), d.getVar("QB_DEFAULT_KERNEL"))
    command = [qemu]
    for variable in ("QB_MACHINE", "QB_MEM", "QB_CPU", "QB_OPT_APPEND",
                     "QB_SERIAL_OPT", "TEST_QEMUPARAMS"):
        command += shlex.split(d.getVar(variable) or "")
    command += ["-kernel", image]
    try:
        result = subprocess.run(command, stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT, text=True,
                                timeout=int(d.getVar("TEST_QEMUBOOT_TIMEOUT")))
    except subprocess.TimeoutExpired as error:
        bb.fatal("QEMU timed out: %s" % error)

    bb.note("QEMU serial output:\n%s" % result.stdout)
    if result.returncode != 0 or expected not in result.stdout:
        bb.fatal("QEMU test failed (exit %s):\n%s" %
                 (result.returncode, result.stdout))
}
