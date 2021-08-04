# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', ...
OVERRIDES:append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

FILESEXTRAPATHS:prepend:autonomy-host := "${THISDIR}/${PN}:"

# The --exclude flag in Busybox tar is required by xenguest-mkimage
SRC_URI:append:autonomy-host = " file://feature_tar_long_options.cfg"
