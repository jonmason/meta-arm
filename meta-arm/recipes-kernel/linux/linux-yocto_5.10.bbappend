ARMFILESPATHS := "${THISDIR}/${PN}:"

COMPATIBLE_MACHINE_generic-arm64 = "generic-arm64"
FILESEXTRAPATHS_prepend_generic-arm64 = "${ARMFILESPATHS}"
SRC_URI_append_generic-arm64 = " \
    file://defconfig.patch \
    "

FILESEXTRAPATHS_prepend_qemuarm64-sbsa = "${ARMFILESPATHS}"
LINUX_VERSION_qemuarm64-sbsa = "5.10.30"
SRCREV_machine_qemuarm64-sbsa = "d6e20b2257ecfa6e796a45a4175863862a28fa11"
SRC_URI_append_qemuarm64-sbsa = " \
    file://defconfig.patch \
    "

LINUX_VERSION_qemuarm64-secureboot = "5.10.21"
SRCREV_machine_qemuarm64-secureboot = "012f78dadb7186c479343b77e97df2925caf681e"
