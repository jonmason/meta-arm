# Machine specific u-boot

FILESEXTRAPATHS_prepend := "${THISDIR}/${BP}:"

#
# FVP BASE
#
SRC_URI_append_fvp-base = " file://u-boot_vexpress_fvp.patch"

#
# FVP BASE ARM32
#
SRC_URI_append_fvp-base-arm32 = " file://0001-Add-vexpress_aemv8a_aarch32-variant.patch"
