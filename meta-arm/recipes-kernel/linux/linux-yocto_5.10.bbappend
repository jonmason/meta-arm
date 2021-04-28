ARMFILESPATHS := "${THISDIR}/${PN}:"

COMPATIBLE_MACHINE_generic-arm64 = "generic-arm64"
FILESEXTRAPATHS_prepend_generic-arm64 = "${ARMFILESPATHS}"
SRC_URI_append_generic-arm64 = " \
    file://defconfig.patch \
    "

FILESEXTRAPATHS_prepend_qemuarm64-sbsa = "${ARMFILESPATHS}"
SRC_URI_append_qemuarm64-sbsa = " \
    file://defconfig.patch \
    "

FILESEXTRAPATHS_prepend_qemuarm64-secureboot = "${ARMFILESPATHS}"
SRC_URI_append_qemuarm64-secureboot = " file://zone_dma_revert.patch"
