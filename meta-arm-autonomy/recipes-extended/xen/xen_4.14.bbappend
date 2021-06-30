# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', ...
OVERRIDES_append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

FILESEXTRAPATHS_prepend_autonomy-host := "${THISDIR}/${PN}-4.14:"

SRC_URI_append_autonomy-host = " \
    file://0001-xen-arm-Throw-messages-for-unknown-FP-SIMD-implement.patch \
    "
