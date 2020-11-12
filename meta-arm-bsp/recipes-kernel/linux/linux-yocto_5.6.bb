KBRANCH = "v5.6/base"

require recipes-kernel/linux/linux-yocto.inc

SRCREV_machine = "e3ac9117b18596b7363d5b7904ab03a7d782b40c"
SRCREV_meta = "b152cd93ea7046a835c869a76085aefdb6ce7421"

SRC_URI = "git://git.yoctoproject.org/linux-yocto.git;name=machine;branch=${KBRANCH}; \
           git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-5.6;destsuffix=${KMETA}"

LINUX_VERSION = "5.6.14"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

PV = "${LINUX_VERSION}+git${SRCPV}"
KMETA = "kernel-meta"
