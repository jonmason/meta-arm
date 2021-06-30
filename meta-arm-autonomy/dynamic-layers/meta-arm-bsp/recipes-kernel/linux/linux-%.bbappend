# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'autonomy-host', ...
OVERRIDES_append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

FILESEXTRAPATHS_prepend_autonomy-host_fvp-base := "${THISDIR}:"

#
# arm-autonomy kmeta extra
#
SRC_URI_append_autonomy-host_fvp-base = " \
    file://arm-autonomy-kmeta-extra;type=kmeta;name=arm-autonomy-kmeta-extra;destsuffix=arm-autonomy-kmeta-extra"

# We need to turn off SVE support in the Linux kernel otherwise Xen is stopping
# Linux kernel with a coredump while trying to access XEN bit of CPACR1 core
# register.
KERNEL_FEATURES_append_autonomy-host_fvp-base = " \
    features/arm-autonomy/disable-arm64-sve.scc"
