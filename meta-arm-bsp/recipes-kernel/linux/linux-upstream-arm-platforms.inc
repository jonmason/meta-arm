DESCRIPTION = "Linux Kernel based on upstream tree"
SECTION = "kernel"
LICENSE = "GPLv2"
SRCREV_FORMAT = "kernel"

require recipes-kernel/linux/linux-yocto.inc

KERNEL_VERSION_SANITY_SKIP = "1"

S = "${WORKDIR}/git"

# Override do_kernel_configme to avoid kernel being assembled into a linux-yocto
# style kernel
# https://www.yoctoproject.org/docs/latest/ref-manual/ref-manual.html#ref-tasks-kernel_configme
do_kernel_configme[noexec] = "1"

# Make sure no branch is defined since here we track a specific version
KBRANCH = ""

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

SRC_URI = "\
        git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux;protocol=https;nobranch=1 \
        "
