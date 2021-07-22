# Machine specific configurations

MACHINE_OPTEE_TEST_REQUIRE ?= ""
MACHINE_OPTEE_TEST_REQUIRE_tc0 = "optee-test-tc0.inc"

require ${MACHINE_OPTEE_TEST_REQUIRE}
