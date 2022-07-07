# Machine specific TFAs

MACHINE_TFA_REQUIRE ?= ""
MACHINE_TFA_REQUIRE:n1sdp = "trusted-firmware-a-n1sdp.inc"

require ${MACHINE_TFA_REQUIRE}
