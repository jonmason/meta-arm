# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "\
            file://0001-plat-arm-a5ds-move-dtb-to-a-new-address.patch \
	    "
