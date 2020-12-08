# Include machine specific SCP configurations

MACHINE_SCP_REQUIRE ?= ""

MACHINE_SCP_REQUIRE_tc0 = "scp-firmware-tc0.inc"
MACHINE_SCP_REQUIRE_juno = "scp-firmware-juno.inc"
MACHINE_SCP_REQUIRE_sgi575 = "scp-firmware-sgi575.inc"

require ${MACHINE_SCP_REQUIRE}
