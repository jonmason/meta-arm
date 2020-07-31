FILESEXTRAPATHS_prepend_gem5-arm64 := "${THISDIR}:"

#
# arm-autonomy kmeta extra
#
SRC_URI_append_gem5-arm64 = " file://arm-autonomy-kmeta-extra-gem5;type=kmeta;name=arm-autonomy-kmeta-extra-gem5;destsuffix=arm-autonomy-kmeta-extra-gem5"

# We need to turn off SVE support in the Linux kernel otherwise Xen is stopping
# Linux kernel with a coredump while trying to access XEN bit of CPACR1 core
# register.
LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE_gem5-arm64 = "${@bb.utils.contains_any('DISTRO_FEATURES', \
                                         'arm-autonomy-host arm-autonomy-guest', \
                                         ' features/arm-autonomy/disable-arm64-sve.scc','',d)}"

KERNEL_FEATURES_append_gem5-arm64 = "${LINUX_ARM_AUTONOMY_DISABLE_ARM64_SVE}"
