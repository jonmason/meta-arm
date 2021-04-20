# This files is added when DISTRO_FEATURES contains arm-autonomy-host

# We need to have xen and ipv4 activated
DISTRO_FEATURES_append = " xen ipv4"
DISTRO_FEATURES_NATIVE_append = " arm-autonomy-host"

# Since meta-virtualization master branch bumped to 4.15+stable we need to
# force the 4.14+stable selection until we validate the new version
PREFERRED_VERSION_xen = "4.14+stable%"
PREFERRED_VERSION_xen-tools = "4.14+stable%"

# Don't include kernels in standard images when building arm-autonomy-host
# If the kernel image is needed in the rootfs the following should be set from
# a bbappend: RDEPENDS_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-image"
RDEPENDS_${KERNEL_PACKAGE_NAME}-base ?= ""

# Require extra machine specific settings from meta-arm-bsp dynamic-layers only
# if meta-arm-bsp is in the bblayers.conf
# Directory for meta-arm-autonomy/dynamic-layers/meta-arm-bsp machine extra settings
ARM_AUTONOMY_ARM_BSP_DYNAMIC_EXTRA_CFGDIR = "${ARM_AUTONOMY_ARM_BSP_DYNAMIC_DIR}/conf/machine"
ARM_AUTONOMY_MACHINE_EXTRA_REQUIRE ?= \
"${ARM_AUTONOMY_ARM_BSP_DYNAMIC_EXTRA_CFGDIR}/arm-autonomy-machine-extra-settings.inc"

require ${@bb.utils.contains('BBFILE_COLLECTIONS', 'meta-arm-bsp', \
                             '${ARM_AUTONOMY_MACHINE_EXTRA_REQUIRE}' , \
                             '', d)}
