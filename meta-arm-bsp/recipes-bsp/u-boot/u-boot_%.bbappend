FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

MACHINE_U-BOOT_REQUIRE ?= ""
MACHINE_U-BOOT_REQUIRE:corstone1000 = "u-boot-corstone1000.inc"
MACHINE_U-BOOT_REQUIRE:fvp-base = "u-boot-fvp-base.inc"
MACHINE_U-BOOT_REQUIRE:juno = "u-boot-juno.inc"

#
# Corstone-500 MACHINE
#
SRC_URI:append:corstone500 = " \
                   file://0001-armv7-adding-generic-timer-access-through-MMIO.patch \
                   file://0002-board-arm-add-corstone500-board.patch"

require ${MACHINE_U-BOOT_REQUIRE}

