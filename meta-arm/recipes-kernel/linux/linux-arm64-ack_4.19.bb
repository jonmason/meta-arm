# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2020 Arm Limited
#


DESCRIPTION = "Linux Android Common Kernel"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${S}/COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

require recipes-kernel/linux/linux-yocto.inc

COMPATIBLE_MACHINE ?= "invalid"

ARCH = "arm64"

SRC_URI = " \
    git://android.googlesource.com/kernel/common.git;protocol=https;branch=android-4.19-q-release \
    "

# ASB-2020-06-05_4.19-q-release tag commit
SRCREV = "ebd43352dd92e56f14a4985a3c99de767fc8f9cf"

S = "${WORKDIR}/git"

LINUX_VERSION ?= "${PV}"
KERNEL_VERSION_SANITY_SKIP = "1"
KBRANCH = ""
