# For Xen we only need the i386 binaries
QEMU_TARGETS = "i386"

PACKAGECONFIG[noaudio] = "--audio-drv-list='',,"
PACKAGECONFIG:append = " noaudio"
PACKAGECONFIG:remove = "fdt sdl kvm"

require recipes-devtools/qemu/qemu-package-split.inc
