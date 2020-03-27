# Add arm-autonomy specific features to the kernel

FILESEXTRAPATHS_prepend := "${THISDIR}:"

#
# arm-autonomy kmeta
#
SRC_URI_append = " file://arm-autonomy-kmeta;type=kmeta;name=arm-autonomy-kmeta;destsuffix=arm-autonomy-kmeta"

# Add xen host drivers to kernel if arm-autonomy-host is activated
KERNEL_FEATURES += "${@bb.utils.contains('DISTRO_FEATURES', \
        'arm-autonomy-host', 'features/arm-autonomy/xen-host.scc', '', d)}"

