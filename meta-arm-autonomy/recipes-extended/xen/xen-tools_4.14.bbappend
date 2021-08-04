# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', ...
OVERRIDES:append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

FILESEXTRAPATHS:prepend:autonomy-host := "${THISDIR}/${PN}-4.14:"

SRC_URI:append:autonomy-host = " file://0001-vif-nat-fix-hostname.patch"
