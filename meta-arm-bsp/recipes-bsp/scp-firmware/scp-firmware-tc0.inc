# TC0 specific SCP configuration

# Intermediate SHA with 2.7 baseline version, required for Theodul DSU
SRCREV = "bc35f4fd2d5e93c77effdeba43c98ddd5038de96"
PV = "2.7.0+git${SRCPV}"

COMPATIBLE_MACHINE = "tc0"

SCP_PLATFORM = "tc0"
FW_TARGETS = "scp"
