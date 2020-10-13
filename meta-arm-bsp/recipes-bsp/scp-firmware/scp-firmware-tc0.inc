# TC0 specific SCP configuration

# Intermediate SHA with 2.6 baseline version
SRC_URI = "gitsm://github.com/ARM-software/SCP-firmware.git;protocol=https"
SRCREV = "6fad1d3e2f82b2ef51e55928ac3a678a75f64ef4"

COMPATIBLE_MACHINE = "tc0"

SCP_PLATFORM = "tc0"
FW_TARGETS = "scp"

PV = "2.6.0+git${SRCPV}"
