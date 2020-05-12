# Add support for Arm Linaro Kernel 5.4 for Arm Platforms (boards or simulators)

SUMMARY = "Linux Kernel Upstream, supported by Arm/Linaro"
LICENSE = "GPLv2"
SECTION = "kernel"

require recipes-kernel/linux/linux-yocto.inc

COMPATIBLE_MACHINE ?= "invalid"

# KBRANCH is set to n1sdp by default as there is no master branch on the repository
KBRANCH = "n1sdp"

SRC_URI = "git://git.linaro.org/landing-teams/working/arm/kernel-release.git;branch=${KBRANCH}; \
           file://0001-menuconfig-mconf-cfg-Allow-specification-of-ncurses-location.patch \
          "
LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

SRCREV = "${AUTOREV}"
LINUX_VERSION ?= "${PV}"
