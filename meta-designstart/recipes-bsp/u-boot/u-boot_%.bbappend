# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 ARM Limited
#

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

UBOOT_MACHINE = "vexpress_aemv8a_a5ds_defconfig"

SRC_URI += "\
	file://0001-skip-creating-libfdt-for-python-for-yocto-build.patch \
	file://0001-rename_sp804_timer_to_mmio_timer.patch \
	file://0001-a5ds_target_support.patch \
	"
