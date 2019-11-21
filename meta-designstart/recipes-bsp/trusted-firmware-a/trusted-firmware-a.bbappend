# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "\
            file://0001-plat-arm-a5ds-dts-uart-clock.patch \
	    "
SRCREV = "af1ac83e0fa4e77aad13e1e8e47b6fcafeb17dbc"
