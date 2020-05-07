FILESEXTRAPATHS_prepend := "${THISDIR}:"

#
# arm-autonomy kmeta extra
#
SRC_URI_append = " file://arm-autonomy-kmeta-extra;type=kmeta;name=arm-autonomy-kmeta-extra;destsuffix=arm-autonomy-kmeta-extra"

# We need to turn off SVE support in the Linux kernel otherwise Xen is stopping
# Linux kernel with a coredump while trying to access XEN bit of CPACR1 core
# register.
LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE = "${@bb.utils.contains_any('DISTRO_FEATURES', \
                                         'arm-autonomy-host arm-autonomy-guest', \
                                         ' features/arm-autonomy/disable-arm64-sve.scc','',d)}"

KERNEL_FEATURES_append_gem5-arm64 = "${LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE}"
KERNEL_FEATURES_append_fvp-base = "${LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE}"
KERNEL_FEATURES_append_foundation-armv8 = "${LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE}"
