KBRANCH ?= "v5.6/standard/base"

require recipes-kernel/linux/linux-yocto.inc

SRCREV_machine = "cd5b55b99dab4da10ffd084f00f2ba088a74f45f"
SRCREV_meta = "b152cd93ea7046a835c869a76085aefdb6ce7421"

SRC_URI = "git://git.yoctoproject.org/linux-yocto.git;name=machine;branch=${KBRANCH}; \
           git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-5.6;destsuffix=${KMETA}"

LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"
LINUX_VERSION = "5.6.19"

DEPENDS += "openssl-native util-linux-native"

PV = "${LINUX_VERSION}+git${SRCPV}"

KMETA = "kernel-meta"
KCONF_BSP_AUDIT_LEVEL = "1"

# Functionality flags
KERNEL_FEATURES:append = " ${KERNEL_EXTRA_FEATURES}"
