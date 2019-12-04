# Machine specific TFAs

MACHINE_TFA_REQUIRE ?= ""

MACHINE_TFA_REQUIRE_foundation-armv8 = "trusted-firmware-a-fvp.inc"
MACHINE_TFA_REQUIRE_fvp-base = "trusted-firmware-a-fvp.inc"

require ${MACHINE_TFA_REQUIRE}
