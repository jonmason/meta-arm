# FVP Base support
COMPATIBLE_MACHINE:fvp-base = "fvp-base"
FILESEXTRAPATHS:prepend:fvp-base := "${THISDIR}/files:"
SRC_URI:append:fvp-base = " file://early-printk.cfg"

# Juno support
COMPATIBLE_MACHINE:juno = "juno"
FILESEXTRAPATHS:prepend:juno := "${THISDIR}/files:"
SRC_URI:append:juno = " file://early-printk.cfg"

# N1SDP support
COMPATIBLE_MACHINE:n1sdp = "n1sdp"
FILESEXTRAPATHS:prepend:n1sdp := "${THISDIR}/files:"
SRC_URI:append:n1sdp = " file://n1sdp.cfg \
                         file://early-printk.cfg"
