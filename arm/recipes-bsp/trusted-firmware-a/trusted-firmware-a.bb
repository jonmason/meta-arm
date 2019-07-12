# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#

SUMMARY = "Trusted Firmware for Cortex-A"
DESCRIPTION = "Trusted Firmware-A"
HOMEPAGE = "https://github.com/ARM-software/arm-trusted-firmware"
LICENSE = "BSD-3-Clause"

TF-A_DEPENDS ?= ""

DEPENDS += " dtc-native coreutils-native"
DEPENDS += " ${TF-A_DEPENDS} "

LIC_FILES_CHKSUM = "file://license.rst;md5=90153916317c204fade8b8df15739cde"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRCREV = "${AUTOREV}"

SRC_URI = "\
  git://github.com/ARM-software/arm-trusted-firmware;protocol=https;nobranch=1 \
  "

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

COMPATIBLE_MACHINE = "(vexpress-a5|vexpress-a32|corstone700|a5ds)"

LDFLAGS[unexport] = "1"

TF-A_PLATFORM ?= "fvp"
TF-A_ARCH ?= "aarch32"
TF-A_DEBUG ?= "1"
TF-A_AARCH32_SP ?= "sp_min"
TF-A_BL33 ?= ""

TF-A_TARGET_IMAGES ?= "fip all"
TF-A_EXTRA_OPTIONS ?= ""

do_compile() {
    mkdir -p ${B}

    oe_runmake -C ${S} BUILD_BASE=${B} \
      BUILD_PLAT=${B}/${TF-A_PLATFORM}/ \
      PLAT=${TF-A_PLATFORM} \
      DEBUG=${TF-A_DEBUG} \
      ARCH=${TF-A_ARCH} \
      CROSS_COMPILE=${TARGET_PREFIX} \
      AARCH32_SP=${TF-A_AARCH32_SP} \
      BL33=${TF-A_BL33} \
      ${TF-A_EXTRA_OPTIONS} \
      ${TF-A_TARGET_IMAGES}
}

do_install() {
	[ -f ${B}/${TF-A_PLATFORM}/bl1.bin ] && install -D -p -m 0644 ${B}/${TF-A_PLATFORM}/bl1.bin ${DEPLOY_DIR_IMAGE}/bl1.bin
	[ -f ${B}/${TF-A_PLATFORM}/bl1/bl1.elf ] && install -D -p -m 0644 ${B}/${TF-A_PLATFORM}/bl1/bl1.elf ${DEPLOY_DIR_IMAGE}/bl1.elf
	install -D -p -m 0644 ${B}/${TF-A_PLATFORM}/fip.bin ${DEPLOY_DIR_IMAGE}/${TF-A_PLATFORM}.fip
}
