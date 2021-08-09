KBRANCH ?= "v5.7/standard/base"

require recipes-kernel/linux/linux-yocto.inc

SRCREV_machine = "6b9830fecd4a87d7ebb4d93484fef00f46d0fa0f"
SRCREV_meta = "b9e6fd082dc5bfb51699809d7119d4b20d280c0b"

SRC_URI = "git://git.yoctoproject.org/linux-yocto.git;name=machine;branch=${KBRANCH}; \
           git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-5.7;destsuffix=${KMETA}"

LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"
LINUX_VERSION = "5.7.19"

DEPENDS += "openssl-native util-linux-native"

PV = "${LINUX_VERSION}+git${SRCPV}"

KMETA = "kernel-meta"
KCONF_BSP_AUDIT_LEVEL = "1"

# Functionality flags
KERNEL_FEATURES:append = " ${KERNEL_EXTRA_FEATURES}"
