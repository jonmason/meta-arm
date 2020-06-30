# TC0 specicif SCP configuration

# Intermediate SHA with 2.6 baseline version
SRCREV_scp    = "ba1db5fb0ee4a520836722f7a694177d461ab716"
# 5.2.0 tag commit
SRCREV_cmsis  = "80cc44bba16cb4c8f495b7aa9709d41ac50e9529"

COMPATIBLE_MACHINE = "tc0"

SCP_PLATFORM = "tc0"
FW_TARGETS = "scp"

PV = "2.6+git${SRCPV}"
