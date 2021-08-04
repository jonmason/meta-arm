FILESEXTRAPATHS:prepend := "${THISDIR}/linux-yocto-5.7:"

SRC_URI:append = " file://coresight-traceid.patch \
                   file://defconfig.patch \
                 "
