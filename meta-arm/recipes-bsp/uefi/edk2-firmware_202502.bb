SRCREV_edk2           ?= "fbe0805b2091393406952e84724188f8c1941837"
SRCREV_edk2-platforms ?= "4ce9e8d02cb447a8506a070f06e68bca95bcbbe0"

# FIXME - clang is having issues with antlr
TOOLCHAIN:aarch64 = "gcc"

require recipes-bsp/uefi/edk2-firmware.inc
