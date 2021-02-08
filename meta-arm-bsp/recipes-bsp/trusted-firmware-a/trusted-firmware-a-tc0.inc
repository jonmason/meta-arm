# TC0 specific TFA configuration

# Intermediate SHA with 2.4 baseline version, required for Theodul DSU
# --- This SRC_URI will be removed once below SRCREV_tfa gets merged to TF-A master
SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https;branch=integration;name=tfa"
SRCREV_tfa = "9bc3007d3bb9363dbd5f6655d2b17d599e22bac4"
PV = "2.4+git${SRCPV}"

DEPENDS += "scp-firmware"

COMPATIBLE_MACHINE = "tc0"

TFA_PLATFORM = "tc0"
TFA_BUILD_TARGET = "all fip"
TFA_UBOOT = "1"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_MBEDTLS = "1"
TFA_DEBUG = "1"

TFA_SPD = "spmd"
TFA_SPMD_SPM_AT_SEL2 = "1"

# Set optee as SP. Set spmc manifest and sp layout file to optee
DEPENDS += "optee-os"

TFA_SP_LAYOUT_FILE = "${RECIPE_SYSROOT}/lib/firmware/sp_layout.json"
TFA_ARM_SPMC_MANIFEST_DTS = "plat/arm/board/tc0/fdts/tc0_spmc_optee_sp_manifest.dts"

EXTRA_OEMAKE += "SCP_BL2=${RECIPE_SYSROOT}/firmware/scp_ramfw.bin"
EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"
