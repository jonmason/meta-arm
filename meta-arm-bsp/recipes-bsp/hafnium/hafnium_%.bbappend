# Machine specific configurations

MACHINE_HAFNIUM_REQUIRE ?= ""
MACHINE_HAFNIUM_REQUIRE:rdv3 ?= "hafnium-rdv3.inc"

require ${MACHINE_HAFNIUM_REQUIRE}
