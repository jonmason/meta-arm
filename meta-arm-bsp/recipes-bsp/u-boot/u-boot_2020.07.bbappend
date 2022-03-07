# Machine specific u-boot

THIS_DIR := "${THISDIR}"
FILESEXTRAPATHS:prepend = "${THIS_DIR}/${BP}:"

#
# Juno KMACHINE
#
SRC_URI:append:juno = " file://u-boot_vexpress_uenv.patch"
