#
# Define early console based on board parameters
#

XEN_CONFIG_EARLY_PRINTK ??= "disable"

EXTRA_OEMAKE += "${@bb.utils.contains('XEN_CONFIG_EARLY_PRINTK', 'disable', \
    '', ' CONFIG_DEBUG=y CONFIG_EARLY_PRINTK=${XEN_CONFIG_EARLY_PRINTK}',d)}"

# Make Xen machine specific
# This ensures that sstate is properly handled and that each machine can have
# its own configuration
PACKAGE_ARCH = "${MACHINE_ARCH}"

