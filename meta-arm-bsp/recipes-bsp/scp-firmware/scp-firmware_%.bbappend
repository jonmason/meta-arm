# Include machine specific SCP configurations

MACHINE_SCP_REQUIRE ?= ""

MACHINE_SCP_REQUIRE_n1sdp = "scp-firmware-n1sdp.inc"
MACHINE_SCP_REQUIRE_tc0 = "scp-firmware-tc0.inc"

require ${MACHINE_SCP_REQUIRE}
