FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# Machine specific settings
XEN_CONFIG_EARLY_PRINTK_juno = "juno"
XEN_CONFIG_EARLY_PRINTK_gem5-arm64 = "vexpress"
XEN_CONFIG_EARLY_PRINTK_fvp-base = "fastmodel"
XEN_CONFIG_EARLY_PRINTK_foundation-armv8 = "fastmodel"

# Foundation-armv8 support
COMPATIBLE_MACHINE_foundation-armv8 = "foundation-armv8"

SRC_URI_append_foundation-armv8 = " file://fvp/defconfig"

# FVP Base support
COMPATIBLE_MACHINE_fvp-base = "fvp-base"

SRC_URI_append_fvp-base = " file://fvp/defconfig"

# Juno support
COMPATIBLE_MACHINE_juno = "juno"

SRC_URI_append_juno = " file://juno/defconfig"

# Gem5 support
# Fix problem with number of interrupts on gem5
SRC_URI_append_gem5-arm64 = " file://4.12.0/0001-xen-arm-Cap-the-number-of-interrupt-lines-for-dom0.patch"

