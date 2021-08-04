# Copyright (C) 2020 Texas Instruments Inc.
# Released under the MIT license (see COPYING.MIT for the terms)

require arm-binary-toolchain.inc

COMPATIBLE_HOST = "(x86_64|aarch64).*-linux"

SUMMARY = "Baremetal GCC for Aarch64 processors"
LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

LIC_FILES_CHKSUM = "${@d.getVar(d.expand("LIC_FILES_CHKSUM_${HOST_ARCH}"))}"
LIC_FILES_CHKSUM:aarch64 = "file://share/doc/gcc/Copying.html;md5=fdf39a58ab6e893f3d83594cef77fa05"
LIC_FILES_CHKSUM:x86-64 = "file://share/doc/gcc/Copying.html;md5=e4bcb5bee0c4a50c06704b0b73fcbe0c"

PROVIDES = "virtual/aarch64-none-elf-gcc"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/gnu-a/${PV}/binrel/gcc-arm-${PV}-${HOST_ARCH}-${BINNAME}.tar.xz;name=gnu-a-${HOST_ARCH}"
SRC_URI[gnu-a-x86_64.sha256sum] = "32abfbc7b24c56542f2a6e6969d6b8787e47f7223e8f2097d84151ebd9f86743"
SRC_URI[gnu-a-aarch64.sha256sum] = "4f9f060e2ca993ec9564054e17b6fdeacb47260e983f766f84f157d00345bf29"

S = "${WORKDIR}/gcc-arm-${PV}-${HOST_ARCH}-${BINNAME}"

UPSTREAM_CHECK_URI = "https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads"
UPSTREAM_CHECK_REGEX = "gcc-arm-(?P<pver>.+)-${HOST_ARCH}-${BINNAME}\.tar\.\w+"
