FILESEXTRAPATHS_prepend := "${THISDIR}:${THISDIR}/linux-yocto:"

SRC_URI_append_qemuarm64-sbsa = " \
    file://defconfig.patch \
    "
