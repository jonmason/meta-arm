# gem5 custom bootloader

LIC_FILES_CHKSUM = "file://COPYING;md5=2d9514d69d8abf88b6e9125e759bf0ab \
                    file://LICENSE;md5=a585e2893cee63d16a1d8bc16c6297ec"

SRC_URI = "git://gem5.googlesource.com/public/gem5;protocol=https;nobranch=1"
RELEASE_TAG = "v20.0.0.1"
SRCREV = "332a9de33db603e0aefedae1e05134db4257ea3e"

PV = "${RELEASE_TAG}"

S = "${WORKDIR}/git"

BPN = "gem5-aarch64-bootloader"

require gem5-aarch64-bootloader.inc
