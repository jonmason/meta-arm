# Machine specific TFAs

MACHINE_TFA_REQUIRE ?= ""
MACHINE_TFA_REQUIRE_tc0 = "trusted-firmware-a-tc0.inc"
MACHINE_TFA_REQUIRE_a5ds = "trusted-firmware-a-a5ds.inc"

require ${MACHINE_TFA_REQUIRE}
