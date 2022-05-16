ARMFILESPATHS := "${THISDIR}/${PN}:"

COMPATIBLE_MACHINE:generic-arm64 = "generic-arm64"
FILESEXTRAPATHS:prepend:generic-arm64 = "${ARMFILESPATHS}"
SRC_URI:append:generic-arm64 = " \
    file://tcpci.cfg \
    "

FILESEXTRAPATHS:prepend:qemuarm64-secureboot = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm64-secureboot = " \
    file://skip-unavailable-memory.patch \
    file://tee.cfg \
    "

FILESEXTRAPATHS:prepend:qemuarm-secureboot = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm-secureboot = " \
    file://tee.cfg \
    "
