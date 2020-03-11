# u-boot_2019 patch for Juno board (Adding boot env)

#
# Patch u-boot to add environment variables from Flash
#

FILESEXTRAPATHS_prepend := "${THISDIR}/files/${MACHINE}:"

SRC_URI_append_juno = " file://u-boot_vexpress_uenv.patch"
