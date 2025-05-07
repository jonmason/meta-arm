# RD V3 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "RdV3"
EDK2_PLATFORM_DSC  = "Platform/ARM/SgiPkg/RdV3/RdV3.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"

COMPATIBLE_MACHINE = "rdv3"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += " file://0001-Platform-ARM-fix-SgiPkg-build-failure.patch;patchdir=edk2-platforms"
