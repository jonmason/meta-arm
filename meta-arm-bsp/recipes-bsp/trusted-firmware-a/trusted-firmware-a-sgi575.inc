# SGI575 specific TFA support

COMPATIBLE_MACHINE = "sgi575"
TFA_PLATFORM       = "sgi575"
TFA_BUILD_TARGET   = "all fip"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_DEBUG          = "1"
TFA_MBEDTLS        = "1"
TFA_UBOOT          = "0"

# Sgi575 needs the UEFI as bl33
DEPENDS += "virtual/uefi-firmware"

EXTRA_OEMAKE += "BL33=${RECIPE_SYSROOT}/firmware/uefi.bin"
EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"
EXTRA_OEMAKE += "CFLAGS=-mbranch-protection=none"
