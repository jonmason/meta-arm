# RD V3 specific SCP configurations and build instructions

COMPATIBLE_MACHINE:rdv3 = "rdv3"
SCP_PRODUCT_GROUP = "neoverse-rd"
SCP_PLATFORM = "rdv3"

EXTRA_OECMAKE += "-D SCP_PLATFORM_VARIANT=0"

SCP_LOG_LEVEL = "INFO"
