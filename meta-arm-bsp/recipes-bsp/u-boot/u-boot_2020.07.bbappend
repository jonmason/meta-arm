# Machine specific u-boot

THIS_DIR := "${THISDIR}"
FILESEXTRAPATHS:prepend = "${THIS_DIR}/${BP}:"

#
# Corstone-500 MACHINE
#
SRC_URI:append:corstone500 = " \
                   file://0001-armv7-adding-generic-timer-access-through-MMIO.patch \
                   file://0002-board-arm-add-corstone500-board.patch"

#
# Juno KMACHINE
#
SRC_URI:append:juno = " file://u-boot_vexpress_uenv.patch"
