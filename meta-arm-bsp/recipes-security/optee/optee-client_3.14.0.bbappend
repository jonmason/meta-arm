# Machine specific configurations

MACHINE_OPTEE_CLIENT_REQUIRE ?= ""
MACHINE_OPTEE_CLIENT_REQUIRE:tc = "optee-client-tc.inc"

require ${MACHINE_OPTEE_CLIENT_REQUIRE}
