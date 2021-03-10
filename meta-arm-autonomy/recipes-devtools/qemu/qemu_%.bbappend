# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', ...
OVERRIDES_append = "${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', ':autonomy-host', '', d)}"

# For Xen we only need the i386 binaries
QEMU_TARGETS_autonomy-host = "i386"

PACKAGECONFIG[noaudio] = "--audio-drv-list='',,"
PACKAGECONFIG_append_autonomy-host = " noaudio"
PACKAGECONFIG_remove_autonomy-host = "fdt sdl kvm"

require ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', 'recipes-devtools/qemu/${BPN}-package-split.inc', '', d)}
