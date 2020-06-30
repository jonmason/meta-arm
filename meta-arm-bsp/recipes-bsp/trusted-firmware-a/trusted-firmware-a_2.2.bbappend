# Machine specific TFAs

MACHINE_TFA_REQUIRE ?= ""
MACHINE_TFA_REQUIRE_fvp-base-arm32 = "trusted-firmware-a-fvp-arm32.inc"
MACHINE_TFA_REQUIRE_sgi575 = "trusted-firmware-a-sgi575.inc"

require ${MACHINE_TFA_REQUIRE}
