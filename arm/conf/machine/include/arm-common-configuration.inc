# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#

IMAGE_FSTYPES += "tar.bz2 wic cpio.gz"

EXTRA_IMAGEDEPENDS_append = " trusted-firmware-a"

PREFERRED_PROVIDER_u-boot ?= "u-boot"
PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot"

UBOOT_SUFFIX ?= "bin"
UBOOT_MACHINE ?= "vexpress_aemv8a_aarch32_defconfig"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-arm"

SERIAL_CONSOLES = "115200;ttyAMA0"
