# RD V3 specific TFA support

COMPATIBLE_MACHINE = "rdv3"
TFA_PLATFORM       = "rdv3"
TFA_BUILD_TARGET   = "all fip"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_DEBUG          = "1"
TFA_MBEDTLS        = "1"
TFA_UBOOT          = "0"
TFA_UEFI           = "1"

#TFA_SPD = "spmd"
#TFA_SP_LAYOUT_FILE = "rdv3_sp_layout.json"

#RMM_BUILD_ENABLED=1
#RMM_CONFIG=rdv3_defcfg
#RMM_BUILD_TYPE=Debug
#TF_A_BUILD_FLAGS="${TF_A_BUILD_FLAGS} ENABLE_RME=1 RMM=$TOP_DIR/rmm COT=cca PLAT_MHU_VERSION=3 MEASURED_BOOT=1"
#EXTRA_OEMAKE += "ENABLE_RME=1 RMM=${TOP_DIR}/rmm COT=cca PLAT_MHU_VERSION=3 MEASURED_BOOT=1"

EXTRA_OEMAKE += "RME_GPT_BITLOCK_BLOCK=0"
#EXTRA_OEMAKE += "NRD_PLATFORM_VARIANT=0"
EXTRA_OEMAKE += "BL32=1 CTX_INCLUDE_PAUTH_REGS=1 BRANCH_PROTECTION=1 CTX_INCLUDE_MTE_REGS=1"
#EXTRA_OEMAKE += "SPMD_SPM_AT_SEL2=1 SPD=spmd BL32=1 CTX_INCLUDE_EL2_REGS=1 CTX_INCLUDE_PAUTH_REGS=1 BRANCH_PROTECTION=1 CTX_INCLUDE_MTE_REGS=1"


EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"

# If GENERATE_COT is set, then tf-a will try to use local poetry install
# to run the python cot-dt2c command.  Disable the local poetry and use
# the provided cot-dt2c.
EXTRA_OEMAKE += "POETRY=''"
DEPENDS += "cot-dt2c-native"


SRC_URI_TRUSTED_FIRMWARE_A = "git://gitlab.arm.com/infra-solutions/reference-design/platsw/trusted-firmware-a.git;protocol=https"
SRCBRANCH = "refinfra"
# SHA not in any branches.  so use RD-INFRA-2025.07.03
SRCREV_tfa = "a4b376b128bb5b91771002f7808566f53c8d9f3a"
# old tf-a requires 3.6.2
SRC_URI_MBEDTLS = "git://github.com/Mbed-TLS/mbedtls;name=mbedtls;protocol=https;destsuffix=${BB_GIT_DEFAULT_DESTSUFFIX}/mbedtls;branch=${SRCBRANCH_MBEDTLS}"
SRCREV_mbedtls = "107ea89daaefb9867ea9121002fbbdf926780e98"

# FIXME - hacking around using the 2.14 based recipe
SRC_URI:remove = "file://0001-feat-build-add-HOSTLDFLAGS-to-pass-flags-to-host-lin.patch"
LIC_FILES_CHKSUM:remove = "file://docs/license.rst;md5=6ed7bace7b0bc63021c6eba7b524039e"
LIC_FILES_CHKSUM += "file://docs/license.rst;md5=1118e32884721c0be33267bd7ae11130"
