# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'autonomy-host', ...
OVERRIDES_append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

FILESEXTRAPATHS_prepend_autonomy-host_fvp-base := "${THISDIR}/${PN}:"

#
# FVP BASE
#
SRC_URI_append_autonomy-host_fvp-base = " file://xen_u-boot_kernel_addr.patch"
