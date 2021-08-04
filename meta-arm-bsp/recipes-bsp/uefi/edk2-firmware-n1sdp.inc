FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " file://Add-mem-regions-to-support.patch;patchdir=${S}/edk2-platforms \
                   file://Introduce-platform-DXE-driver.patch;patchdir=${S}/edk2-platforms \
                   file://Enable-N1SDP-platform-specific-configs.patch;patchdir=${S}/edk2-platforms \
                   file://Configuration-Manager-for-N1SDP.patch;patchdir=${S}/edk2-platforms "

# N1SDP specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "n1sdp"
EDK2_PLATFORM_DSC  = "Platform/ARM/N1Sdp/N1SdpPlatform.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"
EDK2_ARCH          = "AARCH64"

COMPATIBLE_MACHINE = "n1sdp"

# UEFI EDK2 on N1SDP is unable to detect FS2 during boot resulting in launching of
# EDK2 shell instead of launching grub. The startup.nsh will force launching of grub
EFIDIR             = "/EFI/BOOT"
EFI_BOOT_IMAGE     = "bootaa64.efi"

do_deploy:append() {
    EFIPATH=$(echo "${EFIDIR}" | sed 's/\//\\/g')
    printf 'FS2:%s\%s\n' "$EFIPATH" "${EFI_BOOT_IMAGE}" > ${DEPLOYDIR}/startup.nsh
}
