# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2020 Arm Limited
#
require linux-arm64-ack.inc

SRC_URI = " \
    git://android.googlesource.com/kernel/common.git;protocol=https;branch=android11-5.4-lts \
    file://0001-perf-cs-etm-Move-definition-of-traceid_list-global-v.patch \
    file://0002-perf-tests-bp_account-Make-global-variable-static.patch \
    file://0003-perf-bench-Share-some-global-variables-to-fix-build-.patch \
    file://0004-libtraceevent-Fix-build-with-binutils-2.35.patch \
    "

# ASB-2020-07-05_5.4-stable tag commit
SRCREV = "056684c0d252f75c13be4abb7408f692eedab653"
