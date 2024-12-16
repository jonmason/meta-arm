# Copyright (C) 2020 Texas Instruments Inc.
# Released under the MIT license (see COPYING.MIT for the terms)

require arm-binary-toolchain.inc

COMPATIBLE_HOST = "(x86_64|aarch64).*-linux"

SUMMARY = "Arm GNU Toolchain - AArch64 bare-metal target (aarch64-none-elf)"
LICENSE = "GPL-3.0-with-GCC-exception & GPL-3.0-only"

LIC_FILES_CHKSUM:aarch64 = "file://share/doc/gcc/Copying.html;md5=402090210d41f07263e91f760d0d1ea3"
LIC_FILES_CHKSUM:x86-64 = "file://share/doc/gcc/Copying.html;md5=2a62a4d37ddad55da732679acd9edf03"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/gnu/${PV}/binrel/arm-gnu-toolchain-${PV}-${HOST_ARCH}-${BINNAME}.tar.xz;name=gcc-${HOST_ARCH}"
SRC_URI[gcc-aarch64.sha256sum] = "c4f0daab43f78e0d56ec2bdad76b98a0223ce12ce7fc51a6ce82f9cc6c6dfba0"
SRC_URI[gcc-x86_64.sha256sum] = "eb54c4727440d03199a6af9a6d021e77f45410cad39effce4e5a1c10a88b7f04"

S = "${WORKDIR}/arm-gnu-toolchain-${PV}-${HOST_ARCH}-${BINNAME}"

UPSTREAM_CHECK_URI = "https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads"
UPSTREAM_CHECK_REGEX = "arm-gnu-toolchain-(?P<pver>\d+\.\d*\.[A-z]*\d*).*-${HOST_ARCH}-${BINNAME}\.tar\.\w+"
