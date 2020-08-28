# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2020 Arm Limited
#
require linux-arm64-ack.inc

SRC_URI = " \
    git://android.googlesource.com/kernel/common.git;protocol=https;branch=android-4.19-q-release \
    "

# ASB-2020-06-05_4.19-q-release tag commit
SRCREV = "ebd43352dd92e56f14a4985a3c99de767fc8f9cf"
