SUMMARY = "External system Cortex-M3 Firmware"
DESCRIPTION = "Firmware to be loaded and run in External System Harness in\
               support to the main application CPU."
HOMEPAGE = "https://git.linaro.org/landing-teams/working/arm/external-system.git"
DEPENDS = "gcc-arm-none-eabi-native"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://license.md;md5=e44b2531cd6ffe9dece394dbe988d9a0"

SRC_URI = "gitsm://git.linaro.org/landing-teams/working/arm/external-system.git;protocol=https;branch=master"
SRCREV = "41ef76951c5119729c1ea305406f74776da90866"
PV .= "~git${SRCPV}"

COMPATIBLE_MACHINE = "(corstone700-*)"

# PRODUCT is passed to the Makefile to specify the platform to be used
PRODUCT = "corstone-700"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

LDFLAGS[unexport] = "1"

do_compile() {
    oe_runmake -C ${S} V=y \
        BUILD_PATH=${B} \
        PRODUCT=${PRODUCT} \
        CROSS_COMPILE=arm-none-eabi- \
        all
}

do_compile[cleandirs] = "${B}"

do_install() {
    install -D -p -m 0644 ${B}/product/${PRODUCT}/firmware/release/bin/firmware.bin ${D}/firmware/es_flashfw.bin
}

FILES:${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"

inherit deploy

do_deploy() {
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
addtask deploy after do_install
