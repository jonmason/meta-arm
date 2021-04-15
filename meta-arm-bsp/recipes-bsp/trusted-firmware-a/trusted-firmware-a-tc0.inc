# TC0 specific TFA configuration

# Intermediate SHA with 2.4 baseline version, required for Theodul DSU
# --- This SRC_URI will be removed once below SRCREV_tfa gets merged to TF-A master
SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https;branch=integration;name=tfa"
SRCREV_tfa = "8078b5c5a0c2a47710df96412d88df53486e2b29"
PV = "2.4+git${SRCPV}"

FILESEXTRAPATHS_prepend_tc0 := "${THISDIR}/files/tc0:"

SRC_URI_append = " \
    file://0001-product-tc0-Add-support-for-Trusted-Services-Secure-.patch \
    file://0002-tc0-update-GICR-base-address.patch \
    "

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
