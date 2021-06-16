# TC0 specific TFA configuration

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
