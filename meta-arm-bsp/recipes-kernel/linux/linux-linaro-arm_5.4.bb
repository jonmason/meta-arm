# Add support for Arm Linaro Kernel 5.4 for Arm Platforms (boards or simulators)

SUMMARY = "Linux Kernel Upstream, supported by Arm/Linaro"
LICENSE = "GPLv2"
SECTION = "kernel"

require recipes-kernel/linux/linux-yocto.inc

COMPATIBLE_MACHINE ?= "invalid"

# KBRANCH is set to n1sdp by default as there is no master branch on the repository
KBRANCH = "n1sdp"

SRC_URI = "git://git.linaro.org/landing-teams/working/arm/kernel-release.git;nobranch=1 \
           file://0001-menuconfig-mconf-cfg-Allow-specification-of-ncurses-location.patch \
           file://0001-scripts-dtc-Remove-redundant-YYLOC-global-declaratio.patch \
          "
LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

# Refer to commit TAG N1SDP-2020.03.26 since it will not get force pushed
SRCREV = "137cccb0843e63b031acf67d1ca4f6447b8c417c"
LINUX_VERSION ?= "${PV}"
