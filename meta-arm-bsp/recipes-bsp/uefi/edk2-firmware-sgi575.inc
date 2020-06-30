SRC_URI = "\
    gitsm://github.com/tianocore/edk2.git;name=edk2;destsuffix=${S}/edk2;nobranch=1 \
    git://github.com/tianocore/edk2-platforms.git;name=edk2-platforms;destsuffix=${S}/edk2/edk2-platforms;nobranch=1 \
"
# TAGS and commit ID
SRCREV_edk2           = "50528537b2fb0ebdf32c719a0525635c93b905c2"
SRCREV_edk2-platforms = "b972f17b329a85e6aa4d69f240d459839ba8b47c"

# SGI575 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "Sgi575"
EDK2_PLATFORM_DSC  = "SgiPkg/Sgi575/Sgi575.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"
EDK2_ARCH          = "AARCH64"

COMPATIBLE_MACHINE = "sgi575"

PV ?= "202005+git${SRCPV}"
