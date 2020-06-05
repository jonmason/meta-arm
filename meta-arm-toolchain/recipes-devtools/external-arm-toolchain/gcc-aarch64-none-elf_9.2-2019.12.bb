# Copyright (C) 2020 Texas Instruments Inc.
# Released under the MIT license (see COPYING.MIT for the terms)

require gcc-x86host.inc

SUMMARY = "Baremetal GCC for Aarch64 processors"
LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

LIC_FILES_CHKSUM = "file://share/doc/gcc/GNU-Free-Documentation-License.html;md5=cc1e9a49a59ce7e6ae5ef37cd16eca0c"

PROVIDES = "virtual/aarch64-none-elf-gcc"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/gnu-a/${PV}/binrel/gcc-arm-${PV}-x86_64-${BINNAME}.tar.xz"

SRC_URI[sha256sum] = "36d2cbe7c2984f2c20f562ac2f3ba524c59151adfa8ee10f1326c88de337b6d1"

S = "${WORKDIR}/gcc-arm-${PV}-x86_64-${BINNAME}"
