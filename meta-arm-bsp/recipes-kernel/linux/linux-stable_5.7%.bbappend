FILESEXTRAPATHS_prepend := "${THISDIR}/linux-stable-5.7:"

SRC_URI_append = " file://coresight-traceid.patch"
