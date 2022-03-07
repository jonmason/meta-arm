# Recipe for building linaro provided kernel

KBRANCH ?= "latest-4.19-armlt-19.01"

require recipes-kernel/linux/linux-yocto.inc

SRCREV_machine ?= "e97e8d868aba53467039dbef3b7436c857433ae3"
SRCREV_meta ?= "ad6f8b357720ca8167a090713b7746230cf4b314"

SRC_URI = "git://git.linaro.org/landing-teams/working/arm/kernel-release.git;name=machine;branch=${KBRANCH}; \
           git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-4.19;destsuffix=${KMETA} \
           file://0001-menuconfig-mconf-cfg-Allow-specification-of-ncurses-location.patch \
           file://0001-scripts-dtc-Remove-redundant-YYLOC-global-declaratio.patch \
          "

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"
LINUX_VERSION ?= "4.19.0"

DEPENDS += "${@bb.utils.contains('ARCH', 'x86', 'elfutils-native', '', d)}"
DEPENDS += "openssl-native util-linux-native"

PV = "${LINUX_VERSION}+git${SRCPV}"

KMETA = "kernel-meta"
KCONF_BSP_AUDIT_LEVEL = "2"

# Functionality flags
KERNEL_EXTRA_FEATURES ?= "features/netfilter/netfilter.scc"
KERNEL_FEATURES_append = " ${KERNEL_EXTRA_FEATURES}"
KERNEL_FEATURES_append = " ${@bb.utils.contains("TUNE_FEATURES", "mx32", " cfg/x32.scc", "" ,d)}"
KERNEL_FEATURES_append = " ${@bb.utils.contains("DISTRO_FEATURES", "ptest", " features/scsi/scsi-debug.scc", "" ,d)}"
