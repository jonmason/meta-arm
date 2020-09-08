# N1SDP specific TFA support

COMPATIBLE_MACHINE = "n1sdp"
TFA_PLATFORM       = "n1sdp"
TFA_BUILD_TARGET   = "bl31 dtbs"
TFA_INSTALL_TARGET = "bl31 n1sdp-multi-chip n1sdp-single-chip"
TFA_DEBUG          = "1"
TFA_MBEDTLS        = "0"
TFA_UBOOT          = "0"

SRC_URI_append = " \
    file://0001-n1sdp-arm-tf-disable-workaround-for-N1-Erratum-13157.patch \
    "

SRCREV_tfa = "50eee85e044a77ad59f4903a5dad91b266770a1d"

PV = "2.3+git${SRCPV}"
