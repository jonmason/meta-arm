# This files is added when DISTRO_FEATURES contains arm-autonomy-host

ARM_AUTONOMY_HOST_OVERRIDES = ":autonomy-host"

# We need to have xen and ipv4 activated
DISTRO_FEATURES:append = " xen ipv4"
DISTRO_FEATURES_NATIVE:append = " arm-autonomy-host"

# Don't include kernels in standard images when building arm-autonomy-host
# If the kernel image is needed in the rootfs the following should be set from
# a bbappend: RDEPENDS:${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-image"
RDEPENDS:${KERNEL_PACKAGE_NAME}-base ?= ""

# Require extra machine specific settings from meta-arm-bsp dynamic-layers only
# if meta-arm-bsp is in the bblayers.conf
# Directory for meta-arm-autonomy/dynamic-layers/meta-arm-bsp machine extra settings
ARM_AUTONOMY_ARM_BSP_DYNAMIC_EXTRA_CFGDIR = "${ARM_AUTONOMY_ARM_BSP_DYNAMIC_DIR}/conf/machine"
ARM_AUTONOMY_MACHINE_EXTRA_REQUIRE ?= \
"${ARM_AUTONOMY_ARM_BSP_DYNAMIC_EXTRA_CFGDIR}/arm-autonomy-machine-extra-settings.inc"

require ${@bb.utils.contains('BBFILE_COLLECTIONS', 'meta-arm-bsp', \
                             '${ARM_AUTONOMY_MACHINE_EXTRA_REQUIRE}' , \
                             '', d)}
