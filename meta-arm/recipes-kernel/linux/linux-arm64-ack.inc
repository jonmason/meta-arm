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

S = "${WORKDIR}/git"

LINUX_VERSION ?= "${PV}"
KERNEL_VERSION_SANITY_SKIP = "1"
KBRANCH = ""
