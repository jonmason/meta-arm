# Corstone700 specific SCP configurations and build instructions

SUMMARY = "Boot Processor firmware"
DESCRIPTION = "Boot Processor firmware"
DEPENDS += "virtual/trusted-firmware-a"

LIC_FILES_CHKSUM = "file://license.md;md5=e44b2531cd6ffe9dece394dbe988d9a0 \
                    file://cmsis/LICENSE.txt;md5=e3fc50a88d0a364313df4b21ef20c29e"

COMPATIBLE_MACHINE = "(corstone700-*)"
SCP_PLATFORM = "corstone-700"

# boot-firmware project is a fork of scp-firmware
SRC_URI = "gitsm://git.linaro.org/landing-teams/working/arm/boot-firmware.git;protocol=https;branch=master"
SRCREV = "a4dd1b60218b5172a94e6f44c96384b84a77588c"
PV = "0.1.0~git${SRCPV}"

B = "${WORKDIR}/build"

EXTRA_OEMAKE = "PRODUCT='${SCP_PLATFORM}' \
                BUILD_PATH=${B} \
                CROSS_COMPILE='arm-none-eabi-' \
               "
do_compile_append() {
   oe_runmake -C ${S}/tools/spitoc CC=${BUILD_CC} clean all
}

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
