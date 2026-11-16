# Machine specific configurations

MACHINE_TFM_REQUIRE ?= ""
MACHINE_TFM_REQUIRE:corstone1000 = "trusted-firmware-m-corstone1000.inc"
MACHINE_TFM_REQUIRE:rdv3 = "trusted-firmware-m-rdv3.inc"
MACHINE_TFM_REQUIRE:rdv3r1 = "trusted-firmware-m-rdv3r1.inc"

require ${MACHINE_TFM_REQUIRE}
