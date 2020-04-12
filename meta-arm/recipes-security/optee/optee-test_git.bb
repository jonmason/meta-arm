SUMMARY = "OP-TEE sanity testsuite"
DESCRIPTION = "Open Portable Trusted Execution Environment - Test suite"
HOMEPAGE = "https://www.op-tee.org/"

LICENSE = "BSD & GPLv2"
LIC_FILES_CHKSUM = "file://${S}/LICENSE.md;md5=daa2bcccc666345ab8940aab1315a4fa"

inherit python3native
require optee.inc

DEPENDS = "optee-client optee-os python3-pycryptodomex-native"

PV = "3.8.0+git${SRCPV}"

SRCREV = "30481e381cb4285706e7516853495a7699c93b2c"
SRC_URI = "git://github.com/OP-TEE/optee_test.git"

S = "${WORKDIR}/git"

OPTEE_CLIENT_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TEEC_EXPORT         = "${STAGING_DIR_HOST}${prefix}"
TA_DEV_KIT_DIR      = "${STAGING_INCDIR}/optee/export-user_ta"

EXTRA_OEMAKE = " TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
                 OPTEE_CLIENT_EXPORT=${OPTEE_CLIENT_EXPORT} \
                 TEEC_EXPORT=${TEEC_EXPORT} \
                 CROSS_COMPILE_HOST=${TARGET_PREFIX} \
                 CROSS_COMPILE_TA=${TARGET_PREFIX} \
                 V=1 \
               "

do_compile() {
    # Top level makefile doesn't seem to handle parallel make gracefully
    oe_runmake xtest
    oe_runmake ta
}

do_install () {
    install -D -p -m0755 ${S}/out/xtest/xtest ${D}${bindir}/xtest

    # install path should match the value set in optee-client/tee-supplicant
    # default TEEC_LOAD_PATH is /lib
    mkdir -p ${D}${nonarch_base_libdir}/optee_armtz/
    install -D -p -m0444 ${S}/out/ta/*/*.ta ${D}${nonarch_base_libdir}/optee_armtz/
}

FILES_${PN} += "${nonarch_base_libdir}/optee_armtz/"

# Imports machine specific configs from staging to build
PACKAGE_ARCH = "${MACHINE_ARCH}"
