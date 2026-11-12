# Machine specific configurations

MACHINE_TFM_REQUIRE ?= ""
MACHINE_TFM_REQUIRE:corstone1000 = "trusted-firmware-m-corstone1000.inc"
MACHINE_TFM_REQUIRE:tc3 = "trusted-firmware-m-tc3.inc"

require ${MACHINE_TFM_REQUIRE}
