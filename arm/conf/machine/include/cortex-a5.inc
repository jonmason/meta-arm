# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#

DEFAULTTUNE="cortexa5"

require conf/machine/include/tune-cortexa5.inc

TF-A_EXTRA_OPTIONS = "ARM_ARCH_MAJOR=7 ARM_CORTEX_A5=yes \
		     ARM_XLAT_TABLES_LIB_V1=1"
