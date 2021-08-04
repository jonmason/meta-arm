SUMMARY = "Boot Processor firmware for Corstone700"
DESCRIPTION = "Boot Processor firmware"

LICENSE = "BSD-3-Clause & Apache-2.0"
LIC_FILES_CHKSUM = "file://license.md;md5=e44b2531cd6ffe9dece394dbe988d9a0 \
                    file://cmsis/LICENSE.txt;md5=e3fc50a88d0a364313df4b21ef20c29e"

SRC_URI = "gitsm://git.linaro.org/landing-teams/working/arm/boot-firmware.git;protocol=https \
           file://gen-module-race.patch"
SRCREV = "af7eeb1bb8c5a85a5e5a76d48acc6fe864d715a9"
PV = "2020.02.10+git${SRCPV}"

PROVIDES += "virtual/control-processor-firmware"

DEPENDS = "virtual/arm-none-eabi-gcc-native virtual/trusted-firmware-a"

inherit deploy

B = "${WORKDIR}/build"
S = "${WORKDIR}/git"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(corstone700-*)"
SCP_PLATFORM = "corstone-700"

LDFLAGS[unexport] = "1"

do_configure[noexec] = "1"

EXTRA_OEMAKE = "PRODUCT='${SCP_PLATFORM}' \
                BUILD_PATH=${B} \
                CROSS_COMPILE='arm-none-eabi-' \
                V=y \
               "

do_compile() {
    oe_runmake -C ${S}/tools/spitoc CC=${BUILD_CC} all
    oe_runmake -C ${S}
}
do_compile[cleandirs] += "${B}"

do_install() {
    install -D -p -m 0644 ${B}/product/${SCP_PLATFORM}/se_ramfw/release/bin/firmware.bin ${D}/firmware/se_ramfw.bin
    install -D -p -m 0644 ${B}/product/${SCP_PLATFORM}/se_romfw/release/bin/firmware.bin ${D}/firmware/se_romfw.bin
    ${S}/tools/spitoc/spitoc \
        --seram ${D}/firmware/se_ramfw.bin \
        --offset 1  \
        --fip ${RECIPE_SYSROOT}/firmware/fip.bin-${TFA_PLATFORM} \
        --offset  33 \
        --out ${D}/firmware/spitoc.bin
}

FILES:${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"
# Skip QA check for relocations in .text of elf binaries
INSANE_SKIP:${PN} = "textrel"

do_deploy() {
    # Copy the images to deploy directory
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
addtask deploy after do_install
