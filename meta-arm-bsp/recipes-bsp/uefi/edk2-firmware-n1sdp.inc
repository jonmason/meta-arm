EDK2_SRC_URI = "git://git.linaro.org/landing-teams/working/arm/edk2.git"
EDK2_PLATFORMS_SRC_URI = "git://git.linaro.org/landing-teams/working/arm/edk2-platforms.git"

# TAGS and commit ID as per N1SDP-2020.03.26 release
SRCREV_edk2           = "3ff8a6bffabad761279817252014d59b6069d68a"
SRCREV_edk2-platforms = "d9d32e6c8b7456d21ce365486ac563b6be36c20d"

# N1SDP specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "n1sdp"
EDK2_PLATFORM_DSC  = "N1SdpPkg/N1SdpPlatform.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"
EDK2_ARCH          = "AARCH64"

COMPATIBLE_MACHINE = "n1sdp"

PV = "201908+git${SRCPV}"

# UEFI EDK2 on N1SDP is unable to detect FS2 during boot resulting in launching of
# EDK2 shell instead of launching grub. The startup.nsh will force launching of grub
EFIDIR             = "/EFI/BOOT"
EFI_BOOT_IMAGE     = "bootaa64.efi"

do_deploy_append() {
    EFIPATH=$(echo "${EFIDIR}" | sed 's/\//\\/g')
    printf 'FS2:%s\%s\n' "$EFIPATH" "${EFI_BOOT_IMAGE}" > ${DEPLOYDIR}/startup.nsh
}
