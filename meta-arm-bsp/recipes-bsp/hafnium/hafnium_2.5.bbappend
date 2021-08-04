# Machine specific configurations

MACHINE_HAFNIUM_REQUIRE ?= ""
MACHINE_HAFNIUM_REQUIRE:tc0 = "hafnium-tc0.inc"

require ${MACHINE_HAFNIUM_REQUIRE}
