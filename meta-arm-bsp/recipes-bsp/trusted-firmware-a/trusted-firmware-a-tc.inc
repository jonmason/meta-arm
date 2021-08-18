# TC0 specific TFA configuration

# Intermediate SHA with 2.5 baseline version
SRCREV_tfa = "ae5cfc5fe01e2629ff3663a42fb2c585b4d3e7cc"
PV = "2.5+git${SRCPV}"
LIC_FILES_CHKSUM = "file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"

DEPENDS += "scp-firmware"

COMPATIBLE_MACHINE = "(tc?)"

TFA_PLATFORM = "tc"
TFA_BUILD_TARGET = "all fip"
TFA_UBOOT = "1"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_MBEDTLS = "1"
TFA_DEBUG = "1"

TFA_SPD = "spmd"
TFA_SPMD_SPM_AT_SEL2 = "1"

TFA_TARGET_PLATFORM:tc0 = "0"
TFA_TARGET_PLATFORM:tc1 = "1"

EXTRA_OEMAKE += "TARGET_PLATFORM=${TFA_TARGET_PLATFORM}"

# Set optee as SP. Set spmc manifest and sp layout file to optee
DEPENDS += "optee-os"

TFA_SP_LAYOUT_FILE = "${RECIPE_SYSROOT}/lib/firmware/sp_layout.json"
TFA_ARM_SPMC_MANIFEST_DTS = "plat/arm/board/tc/fdts/tc_spmc_optee_sp_manifest.dts"

EXTRA_OEMAKE += "SCP_BL2=${RECIPE_SYSROOT}/firmware/scp_ramfw.bin"
EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"
