# N1SDP specific TFA support

COMPATIBLE_MACHINE = "n1sdp"
TFA_PLATFORM       = "n1sdp"
TFA_BUILD_TARGET   = "bl31 dtbs"
TFA_DEBUG          = "1"
TFA_MBEDTLS        = "0"
TFA_UBOOT          = "0"

SRC_URI_append = " \
    file://0001-n1sdp-arm-tf-disable-workaround-for-N1-Erratum-13157.patch \
    "

SRCREV_tfa = "f0b1864f8e309a41d2eb1c9510f8cd3c7aacbb1d"

PV = "2.3+git${SRCPV}"

do_install_append() {
    install -m 0644 "${BUILD_DIR}/fdts/n1sdp-single-chip.dtb" "${D}/firmware/n1sdp-single-chip.dtb"
    install -m 0644 "${BUILD_DIR}/fdts/n1sdp-multi-chip.dtb" "${D}/firmware/n1sdp-multi-chip.dtb"
}
