# Machine specific TFAs

MACHINE_TFA_REQUIRE ?= ""
MACHINE_TFA_REQUIRE_n1sdp = "trusted-firmware-a-n1sdp.inc"
MACHINE_TFA_REQUIRE_fvp-base-arm32 = "trusted-firmware-a-fvp-arm32.inc"

require ${MACHINE_TFA_REQUIRE}

# TFA referred in release tag N1SDP-2020.03.26
SRCREV_tfa_n1sdp = "cfb3f73344217aa000aaff9d84baad7527af75bf"

PV_n1sdp = "2.2+git${SRCPV}"
