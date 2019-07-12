# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#

SRCREV = "9bed08a2ed8d4915e694e5b4a030bd361b829a52"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=a2c678cfd4a4d97135585cad908541c6"

SRC_URI = "\
  git://git.linaro.org/landing-teams/working/arm/u-boot;protocol=https;nobranch=1 \
  "

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

U-BOOT_PLATFORM = "fvp_ve"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

COMPATIBLE_MACHINE = "(vexpress-a5|vexpress-a32|a5ds)"

do_compile() {
    mkdir -p ${B}

    oe_runmake -C ${S} BUILD_BASE=${B} \
      BUILD_PLAT=${B}/${PLATFORM}/ \
      SUPPORT_ARCH_TIMER=no \
      O=${B}
}
