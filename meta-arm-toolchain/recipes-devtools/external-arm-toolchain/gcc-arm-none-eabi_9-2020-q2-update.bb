# Copyright (C) 2019 Garmin Ltd. or its subsidiaries
# Released under the MIT license (see COPYING.MIT for the terms)

require arm-binary-toolchain.inc

COMPATIBLE_HOST = "(x86_64|aarch64).*-linux"

SUMMARY = "Baremetal GCC for ARM-R and ARM-M processors"
LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

LIC_FILES_CHKSUM = "file://share/doc/gcc-arm-none-eabi/license.txt;md5=c18349634b740b7b95f2c2159af888f5"

PROVIDES = "virtual/arm-none-eabi-gcc"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/${BPN}-${PV}-${HOST_ARCH}-linux.tar.bz2;name=gnu-rm-${HOST_ARCH}"
SRC_URI[gnu-rm-x86_64.sha256sum] = "5adc2ee03904571c2de79d5cfc0f7fe2a5c5f54f44da5b645c17ee57b217f11f"
SRC_URI[gnu-rm-aarch64.sha256sum] = "1f4165c25e2cff80e29870f409862487ba470afd436e245ba3c743108e17b8ac"

UPSTREAM_CHECK_URI = "https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads"
UPSTREAM_CHECK_REGEX = "${BPN}-(?P<pver>.+)-${HOST_ARCH}-linux\.tar\.\w+"
