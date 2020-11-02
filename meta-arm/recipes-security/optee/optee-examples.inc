SUMMARY = "OP-TEE examples"
DESCRIPTION = "Open Portable Trusted Execution Environment - Sample Applications"
HOMEPAGE = "https://github.com/linaro-swg/optee_examples"

LICENSE = "BSD-2-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=cd95ab417e23b94f381dafc453d70c30"

DEPENDS = "optee-client optee-os python3-pycryptodomex-native"

inherit python3native

require optee.inc

SRC_URI = "git://github.com/linaro-swg/optee_examples.git \
           file://0001-make-Pass-ldflags-during-link.patch \
          "

OPTEE_COMPILER = "${@d.getVar('TOOLCHAIN') or 'gcc'}"

EXTRA_OEMAKE = " TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
                 OPTEE_CLIENT_EXPORT=${OPTEE_CLIENT_EXPORT} \
                 TEEC_EXPORT=${TEEC_EXPORT} \
                 HOST_CROSS_COMPILE=${TARGET_PREFIX} \
                 LIBGCC_LOCATE_CFLAGS=--sysroot=${STAGING_DIR_HOST} \
                 COMPILER=${OPTEE_COMPILER} \
                 TA_CROSS_COMPILE=${TARGET_PREFIX} \
                 V=1 \
                 OUTPUT_DIR=${B} \
               "

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

OPTEE_CLIENT_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TEEC_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TA_DEV_KIT_DIR = "${STAGING_INCDIR}/optee/export-user_ta"

do_compile() {
    oe_runmake -C ${S}
}
do_compile[cleandirs] = "${B}"

do_install () {
    mkdir -p ${D}${nonarch_base_libdir}/optee_armtz
    mkdir -p ${D}${bindir}
    install -D -p -m0755 ${B}/ca/* ${D}${bindir}
    install -D -p -m0444 ${B}/ta/* ${D}${nonarch_base_libdir}/optee_armtz
}

FILES_${PN} += "${nonarch_base_libdir}/optee_armtz/"

# Imports machine specific configs from staging to build
PACKAGE_ARCH = "${MACHINE_ARCH}"
