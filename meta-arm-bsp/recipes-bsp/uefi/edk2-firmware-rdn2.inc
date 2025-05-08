# RD N2 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "RdN2"
EDK2_PLATFORM_DSC  = "Platform/ARM/SgiPkg/RdN2/RdN2.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"

COMPATIBLE_MACHINE = "rdn2"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += " file://0001-Platform-ARM-fix-SgiPkg-build-failure.patch;patchdir=edk2-platforms"
