KBRANCH = "v5.3/base"

require recipes-kernel/linux/linux-yocto.inc

SRCREV_machine = "d4f3318ed8fab6316cb7a269b8f42306632a3876"
SRCREV_meta = "8d0ed83a864cc91eef4d2abbc90f13d4ecd1c213"

SRC_URI = "git://git.yoctoproject.org/linux-yocto.git;name=machine;branch=${KBRANCH}; \
           git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-5.4;destsuffix=${KMETA} \
           file://0001-scripts-dtc-Remove-redundant-YYLOC-global-declaratio.patch \
          "

LINUX_VERSION = "5.3.18"
LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

PV = "${LINUX_VERSION}+git${SRCPV}"
KMETA = "kernel-meta"
