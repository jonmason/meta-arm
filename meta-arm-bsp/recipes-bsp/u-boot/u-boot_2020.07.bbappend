# Machine specific u-boot

THIS_DIR := "${THISDIR}"
FILESEXTRAPATHS_prepend = "${THIS_DIR}/${BP}:"

#
# Corstone-500 MACHINE
#
SRC_URI_append_corstone500 = " \
                   file://0001-armv7-adding-generic-timer-access-through-MMIO.patch \
                   file://0002-board-arm-add-corstone500-board.patch"

#
# Juno KMACHINE
#
SRC_URI_append_juno = " \
    file://u-boot_vexpress_uenv.patch \
    file://0002-configs-vexpress-modify-to-boot-compressed-initramfs.patch \
    "
