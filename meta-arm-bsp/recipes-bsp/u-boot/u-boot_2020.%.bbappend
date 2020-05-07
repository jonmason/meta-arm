# u-boot_2020 patch for fvp machinesboard

#
# Patch u-boot to change kernel command line
#

FILESEXTRAPATHS_prepend_fvp-base := "${THISDIR}/files/fvp-common:"
FILESEXTRAPATHS_prepend_foundation-armv8 := "${THISDIR}/files/fvp-common:"
FILESEXTRAPATHS_prepend_juno := "${THISDIR}/files:"

SRC_URI_append_fvp-base = " file://u-boot_vexpress_fvp.patch"
SRC_URI_append_foundation-armv8 = " file://u-boot_vexpress_fvp.patch"
SRC_URI_append_juno = " file://u-boot_vexpress_uenv.patch"
