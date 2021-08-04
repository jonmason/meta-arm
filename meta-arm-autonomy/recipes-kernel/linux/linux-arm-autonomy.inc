# Add arm-autonomy specific features to the kernel

FILESEXTRAPATHS:prepend := "${THISDIR}:"

#
# arm-autonomy kmeta
#
SRC_URI:append = " file://arm-autonomy-kmeta;type=kmeta;name=arm-autonomy-kmeta;destsuffix=arm-autonomy-kmeta"

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
COMPATIBLE_MACHINE:arm64-autonomy-guest = "arm64-autonomy-guest"
KMACHINE:arm64-autonomy-guest = "arm64-autonomy-guest"

# Add Minimal Kernel Configs for Docker runtime
KERNEL_FEATURES += "${@bb.utils.contains('DISTRO_FEATURES', \
        'docker', 'features/arm-autonomy/docker-minimal.scc', '', d)}"

python() {
    from distutils.version import LooseVersion

    kernelVersion = d.getVar('LINUX_VERSION')
    pn = d.getVar('PN')

    if kernelVersion and pn != 'linux-libc-headers' \
       and oe.utils.any_distro_features(d, "arm-autonomy-host arm-autonomy-guest"):
        if LooseVersion(kernelVersion) < '5.9':
           d.appendVar('SRC_URI', ' file://files/0001-arm-arm64-xen-Fix-to-convert-percpu-address-to-gfn-c.patch' )

    if kernelVersion and LooseVersion(kernelVersion) < '5.10':
        if oe.utils.any_distro_features(d, "arm-autonomy-host arm-autonomy-guest"):
            d.appendVar('SRC_URI', ' file://files/0001-xen-arm-do-not-setup-the-runstate-info-page-if-kpti-.patch' )
}
