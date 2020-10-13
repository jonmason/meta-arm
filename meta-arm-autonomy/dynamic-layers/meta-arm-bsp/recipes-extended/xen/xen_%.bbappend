# FVP Base support
COMPATIBLE_MACHINE_fvp-base = "fvp-base"
FILESEXTRAPATHS_prepend_fvp-base := "${THISDIR}/files:"
SRC_URI_append_fvp-base = " file://early-printk.cfg"

# Juno support
COMPATIBLE_MACHINE_juno = "juno"
FILESEXTRAPATHS_prepend_juno := "${THISDIR}/files:"
SRC_URI_append_juno = " file://early-printk.cfg"

# N1SDP support
COMPATIBLE_MACHINE_n1sdp = "n1sdp"
FILESEXTRAPATHS_prepend_n1sdp := "${THISDIR}/files:"
SRC_URI_append_n1sdp = " file://n1sdp.cfg \
                         file://early-printk.cfg"
