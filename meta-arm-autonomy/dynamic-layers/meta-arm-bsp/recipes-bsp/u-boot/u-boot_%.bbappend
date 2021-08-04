# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'autonomy-host', ...
OVERRIDES:append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

FILESEXTRAPATHS:prepend:autonomy-host:fvp-base := "${THISDIR}/${PN}:"

#
# FVP BASE
#
SRC_URI:append:autonomy-host:fvp-base = " file://xen_u-boot_kernel_addr.patch"
