# Copyright (C) 2019 Garmin Ltd. or its subsidiaries
# Released under the MIT license (see COPYING.MIT for the terms)

SUMMARY = "Baremetal GCC for ARM-R and ARM-M processors"
LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

LIC_FILES_CHKSUM = "file://share/doc/gcc-arm-none-eabi/license.txt;md5=c18349634b740b7b95f2c2159af888f5"

PROVIDES = "virtual/arm-none-eabi-gcc"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/${BPN}-${PV}-x86_64-linux.tar.bz2"

SRC_URI[md5sum] = "fe0029de4f4ec43cf7008944e34ff8cc"
SRC_URI[sha256sum] = "bcd840f839d5bf49279638e9f67890b2ef3a7c9c7a9b25271e83ec4ff41d177a"

S = "${WORKDIR}/${BPN}-${PV}"

COMPATIBLE_HOST = "x86_64.*-linux"

do_install() {
    install -d ${D}${datadir}/arm-none-eabi/
    cp -r ${S}/. ${D}${datadir}/arm-none-eabi/

    install -d ${D}${bindir}
    # Symlink all executables into bindir
    for f in ${D}${datadir}/arm-none-eabi/bin/arm-none-eabi-*; do
        lnr $f ${D}${bindir}/$(basename $f)
    done
}

FILES_${PN} = "${datadir} ${bindir}"

INSANE_SKIP_${PN} = "already-stripped libdir staticdev file-rdeps"

INHIBIT_SYSROOT_STRIP = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

BBCLASSEXTEND = "native nativesdk"
