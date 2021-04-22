FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += "file://initialise.patch"

# N1SDP specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "n1sdp"
EDK2_PLATFORM_DSC  = "Platform/ARM/N1SdpPkg/N1SdpPlatform.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"
EDK2_ARCH          = "AARCH64"

COMPATIBLE_MACHINE = "n1sdp"

# UEFI EDK2 on N1SDP is unable to detect FS2 during boot resulting in launching of
# EDK2 shell instead of launching grub. The startup.nsh will force launching of grub
EFIDIR             = "/EFI/BOOT"
EFI_BOOT_IMAGE     = "bootaa64.efi"

do_deploy_append() {
    EFIPATH=$(echo "${EFIDIR}" | sed 's/\//\\/g')
    printf 'FS2:%s\%s\n' "$EFIPATH" "${EFI_BOOT_IMAGE}" > ${DEPLOYDIR}/startup.nsh
}
