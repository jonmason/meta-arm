# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019-2020 Arm Limited
#

LIC_FILES_CHKSUM_corstone700 = "file://license.rst;md5=c709b197e22b81ede21109dbffd5f363"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_corstone700 = "git://${USER}@git.linaro.org/landing-teams/working/arm/arm-tf.git;protocol=https;branch=iota"
SRCREV = "CORSTONE-700-2020.02.10"
