ARMFILESPATHS := "${THISDIR}/files:"

FILESEXTRAPATHS:prepend:qemuarm64-secureboot = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm64-secureboot = " \
    file://tee.cfg \
    "

# for Trusted Services uefi-test tool if SMM-Gateway is included
SRC_URI:append:qemuarm64-secureboot = "\
    ${@bb.utils.contains('MACHINE_FEATURES', 'ts-smm-gateway', 'file://no-strict-devmem.cfg', '' , d)} \
    "

FILESEXTRAPATHS:prepend:qemuarm-secureboot = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm-secureboot = " \
    file://tee.cfg \
    "

FILESEXTRAPATHS:prepend:qemuarm = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm = " \
    file://qemuarm-phys-virt.cfg \
    "

ACPIFILEPATH := "${@bb.utils.contains('TFA_UEFI', '1', "${THISDIR}/files:", '', d)}"
FILESEXTRAPATHS:prepend = "${ACPIFILEPATH}"
SRC_URI:append = " ${@bb.utils.contains('TFA_UEFI', '1', 'file://acpi.cfg', '', d)}"

FFA_TRANSPORT_INCLUDE = "${@bb.utils.contains('MACHINE_FEATURES', 'arm-ffa', 'arm-ffa-transport.inc', '' , d)}"
require ${FFA_TRANSPORT_INCLUDE}

require ${@bb.utils.contains('MACHINE_FEATURES', 'uefi-secureboot', 'linux-yocto-uefi-secureboot.inc', '', d)}
