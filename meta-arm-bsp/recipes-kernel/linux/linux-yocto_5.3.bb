KBRANCH ?= "v5.3/standard/base"

require recipes-kernel/linux/linux-yocto.inc

SRCREV_machine = "d4f3318ed8fab6316cb7a269b8f42306632a3876"
SRCREV_meta = "8d0ed83a864cc91eef4d2abbc90f13d4ecd1c213"

SRC_URI = "git://git.yoctoproject.org/linux-yocto.git;name=machine;branch=${KBRANCH}; \
           git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-5.4;destsuffix=${KMETA}"

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"
LINUX_VERSION = "5.3.18"

DEPENDS += "openssl-native util-linux-native"

PV = "${LINUX_VERSION}+git${SRCPV}"

KMETA = "kernel-meta"
KCONF_BSP_AUDIT_LEVEL = "1"

# Functionality flags
KERNEL_FEATURES:append = " ${KERNEL_EXTRA_FEATURES}"
