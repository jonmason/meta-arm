# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019-2020 Arm Limited
#

SUMMARY = "Linux Kernel provided and supported by Arm/Linaro for Cortex-A32"

KERNEL_IMAGETYPE = "xipImage"

KBUILD_DEFCONFIG = "corstone700_defconfig"

SRC_URI = "git://${USER}@git.linaro.org/landing-teams/working/arm/kernel-release.git;protocol=https;branch=iota"
SRCREV = "CORSTONE-700-2020.02.10"
