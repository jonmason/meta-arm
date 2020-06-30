# Machine specific u-boot

FILESEXTRAPATHS_prepend := "${THISDIR}/files/${MACHINE}:"

SRC_URI_append_a5ds = " file://0001-armv7-add-mmio-timer.patch \
                    file://0002-board-arm-add-designstart-cortex-a5-board.patch"

MACHINE_UBOOT_REQUIRE ?= ""

MACHINE_UBOOT_REQUIRE_tc0 = "u-boot-tc0.inc"

require ${MACHINE_UBOOT_REQUIRE}
