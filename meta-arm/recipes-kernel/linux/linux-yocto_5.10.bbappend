FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

COMPATIBLE_MACHINE_generic-arm64 = "generic-arm64"
SRC_URI_append_generic-arm64 = " \
    file://defconfig.patch \
    "

SRC_URI_append_qemuarm64-sbsa = " \
    file://defconfig.patch \
    "

SRC_URI_append_qemuarm64-secureboot = " file://zone_dma_revert.patch"
