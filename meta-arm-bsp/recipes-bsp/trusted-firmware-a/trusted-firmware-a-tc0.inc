# TCO specific TFA configuration

# Intermediate SHA with 2.3 baseline version
SRCREV_tfa = "00ad74c7afe67b2ffaf08300710f18d3dafebb45"

DEPENDS += "scp-firmware"
DEPENDS += "spm"

# Currenly only test partition images are available to be executed at S-EL1.
SP_AT_SEL1 = "cactus"

# Enable test secure partitions if SP_AT_SEL1 is cactus
DEPENDS += " tf-a-tests "

COMPATIBLE_MACHINE = "tc0"

TFA_PLATFORM = "tc0"
TFA_BUILD_TARGET = "all fip"
TFA_UBOOT = "1"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_MBEDTLS = "1"

EXTRA_OEMAKE += "SCP_BL2=${RECIPE_SYSROOT}/firmware/scp_ramfw.bin"
EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"


do_compile[depends] += " spm:do_deploy "
EXTRA_OEMAKE += " SPD=spmd CTX_INCLUDE_EL2_REGS=1 ARM_ARCH_MINOR=4 BL32=${DEPLOY_DIR_IMAGE}/hafnium.bin"

# Enable test secure partitions if SP_AT_SEL1 is cactus
do_compile[depends] += " tf-a-tests:do_deploy "
EXTRA_OEMAKE += " SP_LAYOUT_FILE=${DEPLOY_DIR_IMAGE}/sp_layout.json "
