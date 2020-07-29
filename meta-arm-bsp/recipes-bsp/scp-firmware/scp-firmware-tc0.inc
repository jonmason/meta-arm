# TC0 specific SCP configuration

# Intermediate SHA with 2.6 baseline version
SRCREV = "ba1db5fb0ee4a520836722f7a694177d461ab716"

COMPATIBLE_MACHINE = "tc0"

SCP_PLATFORM = "tc0"
FW_TARGETS = "scp"

PV = "2.6+git${SRCPV}"
