SUMMARY = "OP-TEE sanity testsuite"
DESCRIPTION = "Open Portable Trusted Execution Environment - Test suite"
HOMEPAGE = "https://www.op-tee.org/"

LICENSE = "BSD & GPLv2"
LIC_FILES_CHKSUM = "file://${S}/LICENSE.md;md5=daa2bcccc666345ab8940aab1315a4fa"

inherit python3native
require optee.inc

# Linking fails on musl due to C++/threads
# https://github.com/OP-TEE/optee_test/issues/458#issuecomment-720540834
COMPATIBLE_HOST_libc-musl = 'null'

DEPENDS = "optee-client optee-os python3-pycryptodomex-native"

SRC_URI = "git://github.com/OP-TEE/optee_test.git \
           file://0001-host-xtest-Adjust-order-of-including-compiler.h.patch \
           file://0002-make-remove-Wno-unsafe-loop-for-clang.patch \ 
           file://0003-make-remove-Wmissing-noreturn-for-clang.patch \
          "

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

EXTRA_OEMAKE += "TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
                 CROSS_COMPILE_HOST=${HOST_PREFIX} \
                 CROSS_COMPILE_TA=${HOST_PREFIX} \
                 O=${B} \
               "

do_compile() {
    cd ${S}
    # Top level makefile doesn't seem to handle parallel make gracefully
    oe_runmake xtest
    oe_runmake ta
}
do_compile[cleandirs] = "${B}"

do_install () {
    install -D -p -m0755 ${B}/xtest/xtest ${D}${bindir}/xtest

    # install path should match the value set in optee-client/tee-supplicant
    # default TEEC_LOAD_PATH is /lib
    mkdir -p ${D}${nonarch_base_libdir}/optee_armtz/
    install -D -p -m0444 ${B}/ta/*/*.ta ${D}${nonarch_base_libdir}/optee_armtz/
}

FILES_${PN} += "${nonarch_base_libdir}/optee_armtz/"

# Imports machine specific configs from staging to build
PACKAGE_ARCH = "${MACHINE_ARCH}"
