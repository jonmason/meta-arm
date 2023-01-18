# Machine specific u-boot

THIS_DIR := "${THISDIR}"
FILESEXTRAPATHS:prepend = "${THIS_DIR}/${BP}:"

#
# Juno KMACHINE
#
SRC_URI:append:juno = " \
    file://u-boot_vexpress_uenv.patch \
    file://0002-configs-vexpress-modify-to-boot-compressed-initramfs.patch \
    "
