# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2021 Arm Limited
#
require linux-arm64-ack.inc

SRC_URI = " \
    git://android.googlesource.com/kernel/common.git;protocol=https;branch=android12-5.10-lts \
    "

# tag: ASB-2021-06-05_12-5.10
SRCREV = "00dc4c64e6592a2e469f7886a6a927778c4a2806"
