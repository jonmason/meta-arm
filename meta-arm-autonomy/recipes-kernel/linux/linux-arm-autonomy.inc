# Add arm-autonomy specific features to the kernel

FILESEXTRAPATHS_prepend := "${THISDIR}:${THISDIR}/files:"

#
# arm-autonomy kmeta
#
SRC_URI_append = " file://arm-autonomy-kmeta;type=kmeta;name=arm-autonomy-kmeta;destsuffix=arm-autonomy-kmeta"

# We need to turn off SVE support in the Linux kernel otherwise Xen is stopping
# Linux kernel with a coredump while trying to access XEN bit of CPACR1 core
# register.
LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE = "${@bb.utils.contains_any('DISTRO_FEATURES', \
                                         'arm-autonomy-host arm-autonomy-guest', \
                                         ' features/arm-autonomy/disable-arm64-sve.scc','',d)}"

KERNEL_FEATURES_append_gem5-arm64 = "${LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE}"
KERNEL_FEATURES_append_fvp-base = "${LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE}"
KERNEL_FEATURES_append_foundation-armv8 = "${LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE}"


# Add xen host drivers to kernel if arm-autonomy-host is activated
KERNEL_FEATURES += "${@bb.utils.contains('DISTRO_FEATURES', \
        'arm-autonomy-host', 'features/arm-autonomy/xen-host.scc', '', d)}"

# Add xen guest drivers to kernel if arm-autonomy-guest is activated
KERNEL_FEATURES += "${@bb.utils.contains('DISTRO_FEATURES', \
        'arm-autonomy-guest', 'features/arm-autonomy/xen-guest.scc', '', d)}"

# Add support for arm64-autonomy-guest machine
COMPATIBLE_MACHINE_arm64-autonomy-guest = "arm64-autonomy-guest"
KMACHINE_arm64-autonomy-guest = "arm64-autonomy-guest"

