# Juno specific TFA support

COMPATIBLE_MACHINE = "juno"
TFA_PLATFORM = "juno"
TFA_DEBUG = "1"
TFA_MBEDTLS = "1"
TFA_UBOOT = "1"
TFA_BUILD_TARGET = "bl1 fip"

# Juno needs the System Control Processor Firmware
DEPENDS += "virtual/scp-firmware"

EXTRA_OEMAKE_append = " SCP_BL2=${RECIPE_SYSROOT}/firmware/scp_bl2.bin"
