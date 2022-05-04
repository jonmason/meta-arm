# Machine specific configurations

DEPENDS = "optee-client optee-os-tadevkit python3-pycryptodome-native"

MACHINE_OPTEE_TEST_REQUIRE ?= ""
MACHINE_OPTEE_TEST_REQUIRE:tc = "optee-test-tc.inc"

require ${MACHINE_OPTEE_TEST_REQUIRE}
