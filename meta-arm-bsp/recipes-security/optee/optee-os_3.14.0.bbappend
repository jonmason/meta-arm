# Machine specific configurations

MACHINE_OPTEE_OS_REQUIRE ?= ""
MACHINE_OPTEE_OS_REQUIRE:tc0 = "optee-os-tc0.inc"

require ${MACHINE_OPTEE_OS_REQUIRE}
