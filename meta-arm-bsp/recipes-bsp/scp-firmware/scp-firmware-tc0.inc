# TC0 specific SCP configuration

# Intermediate SHA with 2.6 baseline version
SRCREV = "fd7c83561a7d76c7681d5d017fb23aa3664c028c"

COMPATIBLE_MACHINE = "tc0"

SCP_PLATFORM = "tc0"
FW_TARGETS = "scp"

PV = "2.6.0+git${SRCPV}"
