# Machine specific configurations

MACHINE_PSA_REQUIRE ?= ""
MACHINE_PSA_REQUIRE:corstone1000 = "psa-arch-tests-corstone1000.inc"

require ${MACHINE_PSA_REQUIRE}
