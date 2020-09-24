# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2020 Arm Limited
#
require linux-arm64-ack.inc

SRC_URI = " \
    git://android.googlesource.com/kernel/common.git;protocol=https;branch=android11-5.4-lts \
    "

# ASB-2020-06-05_5.4-stable tag commit
SRCREV = "2068976fd7b172b64020006efde1ee57af6bbf99"
