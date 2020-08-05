# TCO specific TFA configuration

# Intermediate SHA with 2.3 baseline version
SRCREV_tfa = "2fe7d18b0d99fdf4c4dbf84863bb2036dfebc537"

SRC_URI_append = " ${SRC_URI_MBEDTLS}"

DEPENDS += "scp-firmware"

COMPATIBLE_MACHINE = "tc0"

TFA_PLATFORM = "tc0"
TFA_BUILD_TARGET = "all fip"
TFA_UBOOT = "1"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_MBEDTLS = "1"
TFA_DEBUG = "1"

EXTRA_OEMAKE += "SCP_BL2=${RECIPE_SYSROOT}/firmware/scp_ramfw.bin"
EXTRA_OEMAKE += "MBEDTLS_DIR=mbedtls TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"
