# gem5 custom bootloader

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI = "git://gem5.googlesource.com/public/gem5;protocol=https"

LIC_FILES_CHKSUM = "file://COPYING;md5=2d9514d69d8abf88b6e9125e759bf0ab \
                    file://LICENSE;md5=a585e2893cee63d16a1d8bc16c6297ec"

PV = "git${SRCPV}"

S = "${WORKDIR}/git"

SRCREV = "bcf041f257623e5c9e77d35b7531bae59edc0423"

BPN = "gem5-aarch64-bootloader"

require gem5-aarch64-bootloader.inc
