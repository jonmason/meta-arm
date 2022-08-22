ARMFILESPATHS := "${THISDIR}/files:"

COMPATIBLE_MACHINE:generic-arm64 = "generic-arm64"
FILESEXTRAPATHS:prepend:generic-arm64 = "${ARMFILESPATHS}"
SRC_URI:append:generic-arm64 = " \
    file://generic-arm64-kmeta;type=kmeta;destsuffix=generic-arm64-kmeta \
    "

# for Trusted Services uefi-test tool if SMM-Gateway is included
SRC_URI:append:qemuarm64-secureboot = "\
    ${@bb.utils.contains('MACHINE_FEATURES', 'ts-smm-gateway', 'file://no-strict-devmem.cfg', '' , d)} \
    "

FILESEXTRAPATHS:prepend:qemuarm64-secureboot = "${ARMFILESPATHS}"
FILESEXTRAPATHS:prepend:qemuarm-secureboot = "${ARMFILESPATHS}"
FILESEXTRAPATHS:prepend:qemuarm64 = "${ARMFILESPATHS}"
FILESEXTRAPATHS:prepend:qemuarm = "${ARMFILESPATHS}"

KERNEL_FEATURES:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'optee', 'tee.scc', '', d)}"

FFA_TRANSPORT_INCLUDE = "${@bb.utils.contains('MACHINE_FEATURES', 'arm-ffa', 'arm-ffa-transport.inc', '' , d)}"
require ${FFA_TRANSPORT_INCLUDE}
