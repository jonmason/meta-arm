# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 ARM Limited
#

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

UBOOT_MACHINE = "vexpress_aemv8a_a5ds_defconfig"

SRC_URI += "\
	file://0001-skip-creating-libfdt-for-python-for-yocto-build.patch \
	file://0001-armv7-rename-sp804-timer-to-mmio-timer.patch \
	file://0001-a5ds-add-support-for-target-designstart-A5.patch \
	"
