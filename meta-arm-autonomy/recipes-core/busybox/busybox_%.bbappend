# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', ...
OVERRIDES_append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

FILESEXTRAPATHS_prepend_autonomy-host := "${THISDIR}/${PN}:"

# The --exclude flag in Busybox tar is required by xenguest-mkimage
SRC_URI_append_autonomy-host = " file://feature_tar_long_options.cfg"
