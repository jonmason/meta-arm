# Include machine specific SCP configurations

MACHINE_SCP_REQUIRE ?= ""

MACHINE_SCP_REQUIRE:juno = "scp-firmware-juno.inc"
MACHINE_SCP_REQUIRE:rdn2 = "scp-firmware-rdn2.inc"
MACHINE_SCP_REQUIRE:rdv1 = "scp-firmware-rdv1.inc"
MACHINE_SCP_REQUIRE:sgi575 = "scp-firmware-sgi575.inc"

require ${MACHINE_SCP_REQUIRE}
