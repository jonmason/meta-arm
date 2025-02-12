SRCREV_edk2           ?= "0f3867fa6ef0553e26c42f7d71ff6bdb98429742"
SRCREV_edk2-platforms ?= "2d66a9e048285af8ba4bfe4bdaab37a8e98288b3"

# FIXME - clang is having issues with antlr
TOOLCHAIN:aarch64 = "gcc"

require recipes-bsp/uefi/edk2-firmware.inc
