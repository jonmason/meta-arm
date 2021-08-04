# TC0 specific SCP configuration

# Intermediate SHA with 2.8 baseline version
SRCREV = "67a3612716ad3b839da4209a173404692607c5a1"
PV = "2.8+git${SRCPV}"

# This is incorporated into the SRCREV above
SRC_URI:remove = " \
    file://0001-smt-Make-status-and-length-volatile-for-mod_smt_memo.patch \
    "

COMPATIBLE_MACHINE = "tc0"

SCP_PLATFORM = "tc0"
FW_TARGETS = "scp"
