# xen settings

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

#
# Define early console based on board parameters
#

# This should be set in board.conf or local.conf to enable early printk in xen
XEN_CONFIG_EARLY_PRINTK ??= "disable"

EXTRA_OEMAKE += "${@bb.utils.contains('XEN_CONFIG_EARLY_PRINTK', 'disable', \
    '', ' CONFIG_DEBUG=y CONFIG_EARLY_PRINTK=${XEN_CONFIG_EARLY_PRINTK}',d)}"

# Foundation-armv8 support
COMPATIBLE_MACHINE_foundation-armv8 = "foundation-armv8"

SRC_URI_append_foundation-armv8 = " file://fvp/defconfig"
