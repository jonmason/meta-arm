# Machine specific u-boot

FILESEXTRAPATHS_prepend := "${THISDIR}/${BP}:"

#
# FVP BASE
#

SRC_URI_append_fvp-base = "${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', ' file://xen_u-boot_kernel_addr.patch', '', d)}"
