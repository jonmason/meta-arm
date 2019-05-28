DESCRIPTION = "Linux Kernel provided and supported by ARM and Linaro with \
focus on vexpress and other ARM models and hardware. Trying to be as much \
as possible close to upstream tree."
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"
SRCREV = "${AUTOREV}"
SRCREV_FORMAT = "kernel"

require recipes-kernel/linux/linux-yocto.inc

KERNEL_VERSION_SANITY_SKIP = "1"

S = "${WORKDIR}/git"

COMPATIBLE_MACHINE = "(corstone700)"
