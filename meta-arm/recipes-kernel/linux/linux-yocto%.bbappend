ARMFILESPATHS := "${THISDIR}/files:"

COMPATIBLE_MACHINE:qemuarm-m3 = "${MACHINE}"
KBUILD_DEFCONFIG:qemuarm-m3 = "mps2_defconfig"
KCONFIG_MODE:qemuarm-m3 = "--alldefconfig"

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

FILESEXTRAPATHS:prepend:qemuarm64 = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm64 = " file://efi.cfg"

FILESEXTRAPATHS:prepend:qemuarm = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm = " \
    file://efi.cfg \
    "

FFA_TRANSPORT_INCLUDE = "${@bb.utils.contains('MACHINE_FEATURES', 'arm-ffa', 'arm-ffa-transport.inc', '' , d)}"
require ${FFA_TRANSPORT_INCLUDE}

require ${@bb.utils.contains('MACHINE_FEATURES', 'uefi-secureboot', 'linux-yocto-uefi-secureboot.inc', '', d)}
