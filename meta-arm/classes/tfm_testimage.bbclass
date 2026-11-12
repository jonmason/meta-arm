# SPDX-License-Identifier: MIT

TEST_LOG_DIR ?= "${WORKDIR}/testimage"
TFM_TEST_TIMEOUT ?= "300"
TFM_TEST_MODEL_DEPENDS ?= "qemu-system-native:do_populate_sysroot"

python do_testimage() {
    from oeqa.firmware.tfm import testimage_main
    testimage_main(d)
}

do_testimage[depends] += "${TFM_TEST_MODEL_DEPENDS}"
do_testimage[nostamp] = "1"
addtask testimage after do_compile before do_build
