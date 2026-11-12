require trusted-firmware-m-2.3.1-src.inc
require trusted-firmware-m.inc

SUMMARY = "Trusted Firmware-M regression tests"
PROVIDES = ""
COMPATIBLE_MACHINE = "^$"
DEPENDS += "trusted-firmware-m-scripts-native"
SECURITY_LDFLAGS = ""

SRC_URI:append = " file://tfm-testimage.py"

BUILD_REGRESSION_TESTS = "1"
EXTRA_OECMAKE += "-DTEST_S=ON -DTEST_NS=ON"
TFM_NS_TEST_B = "${WORKDIR}/build-ns"

do_compile:append() {
    cmake -GNinja -S ${TFM_TESTS_DIR}/tests_reg -B ${TFM_NS_TEST_B} \
        -DCONFIG_SPE_PATH=${B}/api_ns \
        -DCMAKE_BUILD_TYPE=${@bb.utils.contains('TFM_DEBUG', '1', 'Debug', 'Release', d)} \
        -DTFM_TOOLCHAIN_FILE=${B}/api_ns/cmake/toolchain_ns_GNUARM.cmake \
        -DFETCHCONTENT_FULLY_DISCONNECTED=ON \
        -DQCBOR_PATH=${S}/external/qcbor \
        -DT_COSE_PATH=${S}/external/t_cose
    cmake --build ${TFM_NS_TEST_B}
}

do_install:append() {
    install -m 0644 ${TFM_NS_TEST_B}/bin/tfm_s_ns_signed.bin ${D}${FIRMWARE_DIR}/
}

do_testimage[depends] += "qemu-system-native:do_populate_sysroot"
do_testimage[nostamp] = "1"
do_testimage() {
    install -d ${WORKDIR}/testimage
    : > ${WORKDIR}/testimage/results.log
    result=0
    python3 ${UNPACKDIR}/tfm-testimage.py \
        --qemu ${STAGING_BINDIR_NATIVE}/qemu-system-arm \
        --machine ${TFM_TEST_QEMU_MACHINE} \
        --bootloader ${B}/bin/bl2.bin \
        --boot-address ${TFM_TEST_BL2_ADDR} \
        --image ${TFM_NS_TEST_B}/bin/tfm_s_ns_signed.bin \
        --image-address ${TFM_TEST_IMAGE_ADDR} \
        --log ${WORKDIR}/testimage/qemu.log \
        --results ${WORKDIR}/testimage/results.log \
        --junit ${LOG_DIR}/oeqa/junit.xml \
        --timeout 300 || result=$?
    if test -f ${WORKDIR}/testimage/results.log; then
        while IFS= read -r line; do
            bbplain "$line"
        done < ${WORKDIR}/testimage/results.log
    fi
    return $result
}
addtask testimage after do_compile before do_build
