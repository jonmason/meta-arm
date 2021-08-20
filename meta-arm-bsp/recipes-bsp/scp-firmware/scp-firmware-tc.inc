# TC0 specific SCP configuration

# Intermediate SHA with 2.8 baseline version
SRCREV:tc0 = "67a3612716ad3b839da4209a173404692607c5a1"
SRCREV:tc1 = "26c858b46824a8d74a7593325a0124c163de65d6"

PV = "2.8.0+git${SRCPV}"

# This is incorporated into the SRCREV above
SRC_URI:remove = " \
    file://0001-smt-Make-status-and-length-volatile-for-mod_smt_memo.patch \
    "

COMPATIBLE_MACHINE = "(tc?)"

SCP_PLATFORM:tc0 = "tc0"
SCP_PLATFORM:tc1 = "tc1"
FW_TARGETS = "scp"
