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

SRCREV_tfa = "dffd5192df41e77e27bb524bfe64d747c1c43522"

PV = "2.3+git${SRCPV}"
