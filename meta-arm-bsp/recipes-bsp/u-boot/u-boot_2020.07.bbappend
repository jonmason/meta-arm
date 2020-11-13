# Machine specific u-boot

THIS_DIR := "${THISDIR}"
FILESEXTRAPATHS_prepend = "${THIS_DIR}/${BP}:"
FILESEXTRAPATHS_prepend_fvp-base = "${THIS_DIR}/${BP}/fvp-common:"
FILESEXTRAPATHS_prepend_foundation-armv8 = "${THIS_DIR}/${BP}/fvp-common:"

#
# Corstone-500 MACHINE
#
SRC_URI_append_corstone500 = " \
                   file://0001-armv7-adding-generic-timer-access-through-MMIO.patch \
                   file://0002-board-arm-add-corstone500-board.patch"

#
# FVP FOUNDATION KMACHINE
#
SRC_URI_append_foundation-armv8 = " file://u-boot_vexpress_fvp.patch"

#
# FVP BASE KMACHINE
#
SRC_URI_append_fvp-base = " file://u-boot_vexpress_fvp.patch"

#
# FVP BASE ARM32 KMACHINE
#
SRC_URI_append_fvp-base-arm32 = " file://0001-Add-vexpress_aemv8a_aarch32-variant.patch"

#
# Juno KMACHINE
#
SRC_URI_append_juno = " file://u-boot_vexpress_uenv.patch"

#
# Total Compute KMACHINE
#
SRC_URI_append_tc0 = " file://0001-Add-support-for-Total-Compute.patch"
