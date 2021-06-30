# For Xen we only need the i386 binaries
QEMU_TARGETS = "i386"

PACKAGECONFIG[noaudio] = "--audio-drv-list='',,"
PACKAGECONFIG_append = " noaudio"
PACKAGECONFIG_remove = "fdt sdl kvm"

require recipes-devtools/qemu/qemu-package-split.inc
