# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'xen', ...
OVERRIDES_append = "${@bb.utils.contains('DISTRO_FEATURES', 'xen', ':xen', '', d)}"

# For Xen we only need the i386 binaries
QEMU_TARGETS_xen = "i386"

PACKAGECONFIG[noaudio] = "--audio-drv-list='',,"
PACKAGECONFIG_append_xen = " virtfs noaudio"
PACKAGECONFIG_remove_xen = "sdl"

# Reduce the qemu package size by splitting it into
# qemu and qemu-xen packages
PACKAGES_prepend_xen := "${PN}-xen"
RDEPENDS_${PN}_xen += "${PN}-xen"
FILES_${PN}-xen_xen = "${bindir}/qemu-system-i386"
RDEPENDS_${PN}-xen_xen += "xen-tools-libxenstore xen-tools-libxenctrl \
    xen-tools-libxenguest"
