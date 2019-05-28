SUMMARY = "Boot Processor firmware"
DESCRIPTION = "Boot Processor firmware"
DEPENDS += " coreutils-native gcc-arm-none-eabi-native trusted-firmware-a "
LICENSE="BSD"
LIC_FILES_CHKSUM = "file://license.md;md5=e44b2531cd6ffe9dece394dbe988d9a0"

# Use Yocto-built python3 executable
inherit python3native

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI = "gitsm://${USER}@git.linaro.org/landing-teams/working/arm/boot-firmware.git;protocol=https;branch=corstone700-19.02"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

COMPATIBLE_MACHINE = "(corstone700)"

PLATFORM = "corstone-700"

LDFLAGS[unexport] = "1"

do_compile() {
   export PATH=${TC_GCC_ARM_NONE_EABI_BIN}:$PATH
   mkdir -p ${B}
   oe_runmake -C ${S} BUILD_BASE=${B} \
      BUILD_PLAT=${B}/${PLATFORM}/ \
      PRODUCT=${PLATFORM} \
      CROSS_COMPILE=arm-none-eabi- \
      clean \
      all
   cp ${S}/build/product/${PLATFORM}/se_ramfw/release/bin/firmware.bin ${B}/se_ramfw.bin
   cp ${S}/build/product/${PLATFORM}/se_romfw/release/bin/firmware.bin ${B}/se_romfw.bin

    oe_runmake -C ${S}/tools/spitoc BUILD_BASE=${B} \
       BUILD_PLAT=${B}/${PLATFORM}/ \
       all
    cp ${S}/tools/spitoc/spitoc ${B}/spitoc
}

do_install() {
	install -D -p -m 0644 ${B}/se_ramfw.bin ${DEPLOY_DIR_IMAGE}/se_ramfw.bin
	install -D -p -m 0644 ${B}/se_romfw.bin ${DEPLOY_DIR_IMAGE}/se_romfw.bin
        ${B}/spitoc --seram ${DEPLOY_DIR_IMAGE}/se_ramfw.bin --offset 1  --fip ${DEPLOY_DIR_IMAGE}/corstone700.fip --offset  33 --out ${DEPLOY_DIR_IMAGE}/spitoc.bin
}
