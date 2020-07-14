# Recipe for building linaro kernel

SUMMARY = "Linux Kernel Upstream, supported by Arm/Linaro"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

inherit kernel
inherit kernel-yocto

SRC_URI = "git://git.linaro.org/landing-teams/working/arm/kernel-release.git;branch=${KBRANCH} \
           git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=${KMETA_BRANCH};destsuffix=kernel-meta \
           file://0001-menuconfig-mconf-cfg-Allow-specification-of-ncurses-location.patch"

DEPENDS += "${@bb.utils.contains('ARCH', 'x86', 'elfutils-native', '', d)}"
DEPENDS += "openssl-native util-linux-native"

LINUX_VERSION ?= "${PV}"
S = "${WORKDIR}/git"
