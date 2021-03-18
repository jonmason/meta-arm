# N1SDP specific TFA support

COMPATIBLE_MACHINE = "n1sdp"
TFA_PLATFORM       = "n1sdp"
TFA_BUILD_TARGET   = "bl31 dtbs"
TFA_INSTALL_TARGET = "bl31 n1sdp-multi-chip n1sdp-single-chip"
TFA_DEBUG          = "1"
TFA_MBEDTLS        = "0"
TFA_UBOOT          = "0"

SRCREV_tfa = "332649da478147b3d03132deb3783dd62fd475d7"
PV = "2.4+git${SRCPV}"
