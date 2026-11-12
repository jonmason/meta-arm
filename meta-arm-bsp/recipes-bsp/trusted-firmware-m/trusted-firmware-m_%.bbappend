# Machine specific configurations

MACHINE_TFM_REQUIRE ?= ""
MACHINE_TFM_REQUIRE:corstone1000 = "trusted-firmware-m-corstone1000.inc"
MACHINE_TFM_REQUIRE:mps3-an547 = "trusted-firmware-m-ethos.inc"
MACHINE_TFM_REQUIRE:corstone300-fvp = "trusted-firmware-m-ethos.inc"

require ${MACHINE_TFM_REQUIRE}
