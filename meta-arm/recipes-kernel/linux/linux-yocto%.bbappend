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

FILESEXTRAPATHS:prepend:qemuarm64 = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm64 = " file://efi.cfg"

FILESEXTRAPATHS:prepend:qemuarm = "${ARMFILESPATHS}"
SRC_URI:append:qemuarm = " \
    file://efi.cfg \
    "
SRC_URI:append:qemuarm = " ${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'file://xen-nopci.cfg', '' , d)}"
KERNEL_FEATURES:remove:qemuarm = "${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'features/drm-bochs/drm-bochs.scc', '' , d)}"

FFA_TRANSPORT_INCLUDE = "${@bb.utils.contains('MACHINE_FEATURES', 'arm-ffa', 'arm-ffa-transport.inc', '' , d)}"
require ${FFA_TRANSPORT_INCLUDE}

require ${@bb.utils.contains('MACHINE_FEATURES', 'uefi-secureboot', 'linux-yocto-uefi-secureboot.inc', '', d)}
