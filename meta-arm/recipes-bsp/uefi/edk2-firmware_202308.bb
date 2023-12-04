SRCREV_edk2           ?= "819cfc6b42a68790a23509e4fcc58ceb70e1965e"
SRCREV_edk2-platforms ?= "88ea1c2b62d44d6a4ebf2626ddaeecbc74f96877"

# FIXME - clang is having issues with antlr
TOOLCHAIN:aarch64 = "gcc"

require recipes-bsp/uefi/edk2-firmware.inc
