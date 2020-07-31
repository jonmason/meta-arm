FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# Machine specific settings
XEN_CONFIG_EARLY_PRINTK_juno = "juno"
XEN_CONFIG_EARLY_PRINTK_fvp-base = "fastmodel"
XEN_CONFIG_EARLY_PRINTK_foundation-armv8 = "fastmodel"
XEN_CONFIG_EARLY_PRINTK_n1sdp = "pl011,0x2a400000"

# Foundation-armv8 support
COMPATIBLE_MACHINE_foundation-armv8 = "foundation-armv8"

SRC_URI_append_foundation-armv8 = " file://fvp/defconfig"

# FVP Base support
COMPATIBLE_MACHINE_fvp-base = "fvp-base"

SRC_URI_append_fvp-base = " file://fvp/defconfig"

# Juno support
COMPATIBLE_MACHINE_juno = "juno"

SRC_URI_append_juno = " file://juno/defconfig"

# N1SDP support
COMPATIBLE_MACHINE_n1sdp = "n1sdp"

SRC_URI_append_n1sdp = " file://n1sdp/defconfig"
