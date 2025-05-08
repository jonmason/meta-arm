# RD N2 specific SCP configurations and build instructions

COMPATIBLE_MACHINE:rdn2 = "rdn2"
SCP_PRODUCT_GROUP = "neoverse-rd"
SCP_PLATFORM = "rdn2"

EXTRA_OECMAKE += "-D SCP_PLATFORM_VARIANT=0"

SCP_LOG_LEVEL = "DEBUG"
