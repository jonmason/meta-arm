SRC_URI = "\
    git://git.linaro.org/landing-teams/working/arm/edk2.git;name=edk2;destsuffix=git/edk2;nobranch=1 \
    git://git.linaro.org/landing-teams/working/arm/edk2-platforms.git;name=edk2-platforms;destsuffix=git/edk2/edk2-platforms;nobranch=1 \
"

# TAGS and commit ID as per N1SDP-2020.03.26 release
SRCREV_edk2           = "3ff8a6bffabad761279817252014d59b6069d68a"
SRCREV_edk2-platforms = "b6bfc4417ff13168d69c4cbf2338f62c89c82dfd"

# N1SDP specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "n1sdp"
EDK2_PLATFORM_DSC  = "N1SdpPkg/N1SdpPlatform.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"
EDK2_ARCH          = "AARCH64"

COMPATIBLE_MACHINE = "n1sdp"

PV = "201908+git${SRCPV}"
