# Include machine specific SCP configurations

MACHINE_SCP_REQUIRE ?= ""

MACHINE_SCP_REQUIRE:n1sdp = "scp-firmware-n1sdp.inc"

require ${MACHINE_SCP_REQUIRE}
