SUMMARY = "Trusted Firmware for Cortex-A"
DESCRIPTION = "Trusted Firmware-A"
HOMEPAGE = "https://github.com/ARM-software/arm-trusted-firmware"
LICENSE = "BSD-3-Clause"
DEPENDS += " dtc-native u-boot gcc-arm-linux-eabi-native"

LIC_FILES_CHKSUM = "file://license.rst;md5=c709b197e22b81ede21109dbffd5f363"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRCREV = "5ba32a7660051464ed1d56129adf2606db54b5e3"

SRC_URI = "git://github.com/ARM-software/arm-trusted-firmware;protocol=https;nobranch=1"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

COMPATIBLE_MACHINE = "(vexpress-a5)"

PLATFORM_vexpress-a5 = "fvp_ve"

LDFLAGS[unexport] = "1"

do_compile_vexpress-a5() {
    export PATH=${STAGING_BINDIR_NATIVE}/gcc-arm-linux-gnueabihf/bin:$PATH
    mkdir -p ${B}

    cp ${DEPLOY_DIR_IMAGE}/u-boot.bin \
       ${B}/

    oe_runmake -C ${S} BUILD_BASE=${B} \
      BUILD_PLAT=${B}/${PLATFORM}/ \
      PLAT=${PLATFORM} \
      ARM_ARCH_MAJOR=7 \
      ARM_CORTEX_A5=yes \
      FVP_HW_CONFIG_DTS=fdts/fvp-ve-Cortex-A5x1.dts \
      ARM_XLAT_TABLES_LIB_V1=1 \
      DEBUG=1 \
      ARCH=aarch32 \
      CROSS_COMPILE=arm-linux-gnueabihf- \
      AARCH32_SP=sp_min \
      BL33=${B}/u-boot.bin \
      fip \
      all
}

do_install() {
	install -D -p -m 0644 ${B}/${PLATFORM}/bl1.bin ${DEPLOY_DIR_IMAGE}/bl1.bin
	install -D -p -m 0644 ${B}/${PLATFORM}/fip.bin ${DEPLOY_DIR_IMAGE}/${PLATFORM}.fip
}
