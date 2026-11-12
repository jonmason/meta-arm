COMPATIBLE_MACHINE = "tc3"
TFA_PLATFORM = "tc"
TFA_BUILD_TARGET = "all fip"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_UBOOT = "1"
TFA_MBEDTLS = "1"
TFA_DEBUG = "1"

DEPENDS += "scp-firmware cot-dt2c-native"
EXTRA_OEMAKE += "TARGET_PLATFORM=3 SCP_BL2=${RECIPE_SYSROOT}/firmware/scp-firmware/scp_runtime.bin"
EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                 ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"
EXTRA_OEMAKE += "ARM_GPT_SUPPORT=1 PSA_FWU_SUPPORT=1 host-poetry=''"
