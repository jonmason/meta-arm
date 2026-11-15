# RD V3 specific SCP configurations and build instructions

COMPATIBLE_MACHINE:rdv3 = "rdv3"
SCP_PRODUCT_GROUP = "neoverse-rd"
SCP_PLATFORM = "rdv3"
SCP_DEBUG = "1"
FW_TARGETS = "scp mcp lcp"
FW_INSTALL = "ramfw"

SRC_URI_SCP_FIRMWARE = "gitsm://gitlab.arm.com/infra-solutions/reference-design/platsw/scp-firmware.git;protocol=https"
SRCBRANCH = "refinfra"
SRCREV = "08eb76121af4716386faed8c6524664d994f7129"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += "file://0001-rdv3-Wait-longer-for-RSE-SYSTOP-sync.patch"

EXTRA_OECMAKE += "-D SCP_PLATFORM_VARIANT=0"
EXTRA_OECMAKE += "-D PLAT_RESET_TO_BL31=0"

SCP_LOG_LEVEL = "INFO"
