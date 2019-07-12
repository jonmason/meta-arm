# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#

DESCRIPTION = "Linux Kernel provided and supported by Arm and Linaro with \
focus on vexpress and other Arm models and hardware. Trying to be as much \
as possible close to upstream tree."
SECTION = "kernel"
LICENSE = "GPLv2"
SRCREV_FORMAT = "kernel"

require recipes-kernel/linux/linux-yocto.inc

KERNEL_VERSION_SANITY_SKIP = "1"

S = "${WORKDIR}/git"

COMPATIBLE_MACHINE = "(vexpress-a5|vexpress-a32|corstone700|a5ds)"

# Override do_kernel_configme to avoid kernel being assembled into a linux-yocto style kernel
# https://www.yoctoproject.org/docs/1.8/ref-manual/ref-manual.html#ref-tasks-kernel_configme
do_kernel_configme() {
}

KBRANCH = ""
LINUX_VERSION ?= "5.2"

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

SRC_URI = "\
	  git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux;protocol=https;nobranch=1 \
	"

SRCREV = "v5.2"
