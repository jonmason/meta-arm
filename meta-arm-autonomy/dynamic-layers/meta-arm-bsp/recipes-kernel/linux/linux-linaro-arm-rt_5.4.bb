# This recipe provides the kernel with PREEMPT_RT patches and is based on
# linux-linaro-arm_5.4.bb. Set PREFERRED_PROVIDER_virtual/kernel to
# linux-linaro-arm-rt to enable it as the default kernel.
require linux-linaro-arm_5.4.bb


#
# Include preempt-rt patches
#
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-5.4:"
SRC_URI_append = " \
    https://cdn.kernel.org/pub/linux/kernel/projects/rt/5.4/older/patch-5.4.3-rt1.patch.gz;name=rt-patch \
    file://0001-xen-use-handle_fasteoi_irq-to-handle-xen-dynamic-eve.patch \
    "
SRC_URI[rt-patch.sha256sum] = "6b92ba32c7ce30919c9b66e49e5f1dce58e1f8bd92fef91e548d6f2d434a2b39"

LINUX_KERNEL_TYPE = "preempt-rt"

KERNEL_FEATURES += "features/arm-autonomy/preempt-rt-extras.scc"
