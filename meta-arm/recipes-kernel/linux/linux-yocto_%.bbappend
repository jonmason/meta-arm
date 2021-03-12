FILESEXTRAPATHS_prepend := "${THISDIR}:${THISDIR}/linux-yocto:"

SRC_URI_append_qemuarm64-sbsa = " \
    file://defconfig.patch \
    "

COMPATIBLE_MACHINE_generic-arm64 = "generic-arm64"

SRC_URI_append_generic-arm64 = " \
    file://defconfig.patch \
    "
