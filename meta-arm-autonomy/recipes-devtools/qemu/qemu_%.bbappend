# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'xen', ...
OVERRIDES_append = "${@bb.utils.contains('DISTRO_FEATURES', 'xen', ':xen', '', d)}"

# For Xen we only need the i386 binaries
QEMU_TARGETS_xen = "i386"

PACKAGECONFIG[noaudio] = "--audio-drv-list='',,"
PACKAGECONFIG_append_xen = " noaudio"
PACKAGECONFIG_remove_xen = "fdt sdl kvm"

require ${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'recipes-devtools/qemu/${BPN}-package-split.inc', '', d)}
