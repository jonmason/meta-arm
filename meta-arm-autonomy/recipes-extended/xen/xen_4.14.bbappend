FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-4.14:"

SRC_URI += " \
    file://0001-xen-arm-Throw-messages-for-unknown-FP-SIMD-implement.patch \
    "
