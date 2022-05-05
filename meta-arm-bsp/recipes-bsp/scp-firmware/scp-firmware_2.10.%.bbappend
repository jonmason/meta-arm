# Include machine specific SCP configurations

MACHINE_SCP_REQUIRE ?= ""

MACHINE_SCP_REQUIRE:tc = "scp-firmware-tc.inc"

require ${MACHINE_SCP_REQUIRE}
