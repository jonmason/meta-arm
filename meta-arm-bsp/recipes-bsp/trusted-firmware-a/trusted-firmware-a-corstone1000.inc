# Corstone1000 64-bit machines specific TFA support

COMPATIBLE_MACHINE = "(corstone1000)"

SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https;name=tfa"

# TF-A master branch with all Corstone1000 patches merged
SRCREV_tfa = "459b24451a0829460783ce8dfa15561e36d901d8"
PV .= "+git${SRCREV_tfa}"

LIC_FILES_CHKSUM="file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde file://mbedtls/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/corstone1000:"
SRC_URI:append = " \
                 file://0001-Rename-Diphda-to-corstone1000.patch \
                 file://0002-plat-arm-corstone1000-made-changes-to-accommodate-3M.patch \
                 file://0003-corstone1000-implement-platform-specific-psci-reset.patch \
                 file://0004-plat-arm-corstone1000-change-base-address-of-FIP-in-the-fl.patch   \
                 file://0005-plat-arm-corstone1000-identify-which-bank-to-load-fip-from.patch   \
                 "

TFA_DEBUG = "1"
TFA_UBOOT = "1"
TFA_MBEDTLS = "1"
TFA_BUILD_TARGET = "bl2 bl31 fip"

# Enabling Secure-EL1 Payload Dispatcher (SPD)
TFA_SPD = "spmd"
# Cortex-A35 supports Armv8.0-A (no S-EL2 execution state).
# So, the SPD SPMC component should run at the S-EL1 execution state
TFA_SPMD_SPM_AT_SEL2 = "0"

# BL2 loads BL32 (optee). So, optee needs to be built first:
DEPENDS += "optee-os"

EXTRA_OEMAKE:append = " \
                        ARCH=aarch64 \
                        TARGET_PLATFORM=${TFA_TARGET_PLATFORM} \
                        ENABLE_STACK_PROTECTOR=strong \
                        ENABLE_PIE=1 \
                        BL2_AT_EL3=1 \
                        CREATE_KEYS=1 \
                        GENERATE_COT=1 \
                        TRUSTED_BOARD_BOOT=1 \
                        COT=tbbr \
                        ARM_ROTPK_LOCATION=devel_rsa  \
                        ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem \
                        BL32=${RECIPE_SYSROOT}/lib/firmware/tee-pager_v2.bin \
                        LOG_LEVEL=50 \
                        "

# trigger TF-M build so TF-A binaries get signed
do_deploy[depends]+= "virtual/trusted-firmware-m:do_prepare_recipe_sysroot"
