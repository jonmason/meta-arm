# This files is added when DISTRO_FEATURES contains arm-autonomy-host

# We need to have xen and ipv4 activated
DISTRO_FEATURES_append = " xen ipv4"
DISTRO_FEATURES_NATIVE_append = " arm-autonomy-host"

# Don't include kernels in standard images when building arm-autonomy-host
# If the kernel image is needed in the rootfs the following should be set from
# a bbappend: RDEPENDS_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-image"
RDEPENDS_${KERNEL_PACKAGE_NAME}-base ?= ""
