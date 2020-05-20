# Copyright (C) 2020 Texas Instruments Inc.
# Released under the MIT license (see COPYING.MIT for the terms)

SUMMARY = "Baremetal GCC for Aarch64 processors"
LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

LIC_FILES_CHKSUM = "file://share/doc/gcc/GNU-Free-Documentation-License.html;md5=cc1e9a49a59ce7e6ae5ef37cd16eca0c"

PROVIDES = "virtual/aarch64-none-elf-gcc"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/gnu-a/9.2-2019.12/binrel/gcc-arm-${PV}-x86_64-aarch64-none-elf.tar.xz"

SRC_URI[sha256sum] = "36d2cbe7c2984f2c20f562ac2f3ba524c59151adfa8ee10f1326c88de337b6d1"

S = "${WORKDIR}/gcc-arm-${PV}-x86_64-aarch64-none-elf"

COMPATIBLE_HOST = "x86_64.*-linux"

do_install() {
    install -d ${D}${datadir}/aarch64-none-elf/
    cp -r ${S}/. ${D}${datadir}/aarch64-none-elf/

    install -d ${D}${bindir}
    # Symlink all executables into bindir
    for f in ${D}${datadir}/aarch64-none-elf/bin/aarch64-none-elf-*; do
        lnr $f ${D}${bindir}/$(basename $f)
    done
}

FILES_${PN} = "${datadir} ${bindir}"

INSANE_SKIP_${PN} = "already-stripped libdir staticdev file-rdeps"

INHIBIT_SYSROOT_STRIP = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

BBCLASSEXTEND = "native nativesdk"
