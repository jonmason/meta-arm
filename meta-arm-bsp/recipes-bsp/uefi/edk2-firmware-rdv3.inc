# RD V3 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "RdV3"
EDK2_PLATFORM_DSC  = "Platform/ARM/SgiPkg/RdV3/RdV3.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"

COMPATIBLE_MACHINE = "rdv3"

# Match the EDK2 releases used by the RD-INFRA-2025.07.03 stack.
SRC_URI_EDK2 = "gitsm://gitlab.arm.com/infra-solutions/reference-design/platsw/edk2.git;protocol=https"
SRC_URI_EDK2_PLATFORMS = "git://gitlab.arm.com/infra-solutions/reference-design/platsw/edk2-platforms.git;protocol=https"
SRCBRANCH_edk2 = "refinfra"
SRCBRANCH_edk2_platforms = "refinfra"
SRCREV_edk2 = "dd25905d63ec72d6e06804155fda1098d10da19e"
SRCREV_edk2-platforms = "d504fc6d655d4cc07687eee02c668ccaadfe85ce"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append = " file://0001-Changes-in-acpica-20260408-are-now-causing-issues-wi.patch;patchdir=edk2-platforms"
SRC_URI:remove = "file://0001-DynamicTablesPkg-fix-SmbiosType2Genertor-build-failu.patch"
