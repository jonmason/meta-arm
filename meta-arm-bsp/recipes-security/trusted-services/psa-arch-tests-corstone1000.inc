FILESEXTRAPATHS:prepend := "${THISDIR}/psa-arch-tests/corstone1000:"

DEPENDS += "cmake-native"

export CMAKE_BUILD_PARALLEL_LEVEL
CMAKE_BUILD_PARALLEL_LEVEL = "${@oe.utils.parallel_make(d, True)}"

COMPATIBLE_MACHINE = "corstone1000"

SRC_URI:append = "\
    file://0001-psa-arch-test-sysroot_compiler_flags_fix.patch \
    file://0002-arm-bsp-psa-arch-test-Fixing-psa-arch-tests-cmake.patch \
    file://0003-corstone1000-port-crypto-config.patch;patchdir=../psa-arch-tests \
    "

FILES:${PN} += "${libdir}/libts.so*  ${libdir}/deployments  ${bindir}/psa-*"
FILES:${PN}-dev = "${includedir}/deployments/psa-api-test/"

INSANE_SKIP:${PN} += "rpaths"

do_configure() {
    for PSA_API_TEST in ${PSA_API_TESTS}; do
        cmake \
        -DSYSROOT_YOCTO=${RECIPE_SYSROOT} \
        -S ${S}/$PSA_API_TEST -B "${B}/$PSA_API_TEST"
    done
}

do_compile() {
    for PSA_API_TEST in ${PSA_API_TESTS}; do
        cmake --build "${B}/$PSA_API_TEST"
    done
}

do_install() {
    for PSA_API_TEST in ${PSA_API_TESTS}; do
        install -d -m 0755 ${D}${libdir}/${PSA_API_TEST}
        install -d -m 0755 ${D}${includedir}/${PSA_API_TEST}
        install -m 0755 ${B}/${PSA_API_TEST}/libts_install/arm-linux/lib/*.so* ${D}${libdir}
	install -d -m 0755 ${B}/${PSA_API_TEST}/libts_install/arm-linux/include ${D}${includedir}/${PSA_API_TEST}
	psafile_fullpath=`ls ${B}/${PSA_API_TEST}/psa-*`
	psafile_filename="`basename -s .bin ${psafile_fullpath}`"
        install -D -p -m 0755 ${psafile_fullpath} ${D}/${bindir}/${psafile_filename}
    done
}
