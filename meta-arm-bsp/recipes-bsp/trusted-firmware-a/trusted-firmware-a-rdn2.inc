# RD N2 specific TFA support

COMPATIBLE_MACHINE = "rdn2"
TFA_PLATFORM       = "rdn2"
TFA_BUILD_TARGET   = "all fip"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_DEBUG          = "1"
TFA_UBOOT          = "0"
TFA_UEFI           = "1"

EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"

# Use the provided cot-dt2c instead of TF-A's Poetry environment.
EXTRA_OEMAKE += "host-poetry=''"
DEPENDS += "cot-dt2c-native"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/rdn2:"
SRC_URI += " \
    file://0001-rdn2-add-pcie-mmap.patch \
    file://0002-rdn2-save-sve-context.patch \
"
