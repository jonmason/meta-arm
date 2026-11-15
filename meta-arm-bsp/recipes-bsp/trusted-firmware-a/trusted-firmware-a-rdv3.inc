# RD V3 specific TFA support

COMPATIBLE_MACHINE = "rdv3"
TFA_PLATFORM       = "rdv3"
TFA_BUILD_TARGET   = "all fip"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_DEBUG          = "1"
TFA_MBEDTLS        = "1"
TFA_UBOOT          = "0"
TFA_UEFI           = "1"

EXTRA_OEMAKE += "RME_GPT_BITLOCK_BLOCK=0"
EXTRA_OEMAKE += "NRD_PLATFORM_VARIANT=0"
EXTRA_OEMAKE += "ENABLE_RME=1"
EXTRA_OEMAKE += "ENABLE_BRBE_FOR_NS=1"
EXTRA_OEMAKE += "RMM=${RECIPE_SYSROOT}/firmware/rmm.img"
EXTRA_OEMAKE += "COT=cca MEASURED_BOOT=1 PLAT_RESET_TO_BL31=0"
DEPENDS += "trusted-firmware-rmm"
BUILD_DIR:rdv3 = "${B}/${TFA_PLATFORM}/0/${@'debug' if d.getVar('TFA_DEBUG') == '1' else 'release'}"
EXTRA_OEMAKE += "CTX_INCLUDE_PAUTH_REGS=1 BRANCH_PROTECTION=1 CTX_INCLUDE_MTE_REGS=1"


EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"

# If GENERATE_COT is set, then tf-a will try to use local poetry install
# to run the python cot-dt2c command.  Disable the local poetry and use
# the provided cot-dt2c.
EXTRA_OEMAKE += "POETRY=''"
DEPENDS += "cot-dt2c-native"


SRC_URI_TRUSTED_FIRMWARE_A = "git://gitlab.arm.com/infra-solutions/reference-design/platsw/trusted-firmware-a.git;protocol=https"
SRCBRANCH = "refinfra"
# Match the RD-INFRA-2025.07.03 software release.
SRCREV_tfa = "a4b376b128bb5b91771002f7808566f53c8d9f3a"
# This TF-A revision uses Mbed TLS 3.6.2 as an external source.
TFA_MBEDTLS_DIR = "mbedtls"
EXTRA_OEMAKE += "MBEDTLS_DIR=${TFA_MBEDTLS_DIR}"
LICENSE:append = " AND Apache-2.0"
SRC_URI_MBEDTLS = "gitsm://github.com/Mbed-TLS/mbedtls.git;name=mbedtls;protocol=https;destsuffix=${BB_GIT_DEFAULT_DESTSUFFIX}/mbedtls;branch=mbedtls-3.6"
SRCREV_mbedtls = "107ea89daaefb9867ea9121002fbbdf926780e98"
SRC_URI:append = " ${SRC_URI_MBEDTLS}"
SRCREV_FORMAT:append = "_mbedtls"
LIC_FILES_CHKSUM:append = " file://mbedtls/LICENSE;md5=379d5819937a6c2f1ef1630d341e026d"

# This fork predates the host-linker patch and has a different license checksum.
SRC_URI:remove = "file://0001-feat-build-add-HOSTLDFLAGS-to-pass-flags-to-host-lin.patch"
LIC_FILES_CHKSUM:remove = "file://docs/license.rst;md5=6ed7bace7b0bc63021c6eba7b524039e"
LIC_FILES_CHKSUM += "file://docs/license.rst;md5=1118e32884721c0be33267bd7ae11130"
