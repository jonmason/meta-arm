# Add arm-autonomy specific features to the kernel

FILESEXTRAPATHS_prepend := "${THISDIR}:"

#
# arm-autonomy kmeta
#
SRC_URI_append = " file://arm-autonomy-kmeta;type=kmeta;name=arm-autonomy-kmeta;destsuffix=arm-autonomy-kmeta"

# Add common Xen (host and guest) configs and patches
KERNEL_FEATURES += "${@bb.utils.contains_any('DISTRO_FEATURES', \
        'arm-autonomy-host arm-autonomy-guest', \
        'features/arm-autonomy/xen-common.scc', '', d)}"


# Add xen host drivers to kernel if arm-autonomy-host is activated
KERNEL_FEATURES += "${@bb.utils.contains('DISTRO_FEATURES', \
        'arm-autonomy-host', \
        'features/arm-autonomy/xen-host.scc \
         features/arm-autonomy/xen-host-iptables.scc', \
        '', d)}"


# Add xen guest drivers to kernel if arm-autonomy-guest is activated
KERNEL_FEATURES += "${@bb.utils.contains('DISTRO_FEATURES', \
        'arm-autonomy-guest', 'features/arm-autonomy/xen-guest.scc', '', d)}"


# Add support for arm64-autonomy-guest machine
COMPATIBLE_MACHINE_arm64-autonomy-guest = "arm64-autonomy-guest"
KMACHINE_arm64-autonomy-guest = "arm64-autonomy-guest"

# Add Minimal Kernel Configs for Docker runtime
KERNEL_FEATURES += "${@bb.utils.contains('DISTRO_FEATURES', \
        'docker', 'features/arm-autonomy/docker-minimal.scc', '', d)}"
