FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

# The --exclude flag in Busybox tar is required by xenguest-mkimage
SRC_URI += "file://feature_tar_long_options.cfg"
