require trusted-firmware-m.inc
inherit tfm_testimage

SUMMARY = "Trusted Firmware-M regression tests"
PROVIDES = ""
COMPATIBLE_MACHINE ?= "invalid"
DEPENDS += "trusted-firmware-m-scripts-native"
SECURITY_LDFLAGS = ""

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
