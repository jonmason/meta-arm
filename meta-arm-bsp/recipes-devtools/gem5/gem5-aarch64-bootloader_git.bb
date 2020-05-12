# gem5 custom bootloader

LIC_FILES_CHKSUM = "file://COPYING;md5=2d9514d69d8abf88b6e9125e759bf0ab \
                    file://LICENSE;md5=a585e2893cee63d16a1d8bc16c6297ec"

# The recipe is currently using a version in the release staging branch of gem5
# until version 20 is released
SRC_URI = "git://gem5.googlesource.com/public/gem5;protocol=https;branch=release-staging-v20.0.0.0"

PV = "git${SRCPV}"

S = "${WORKDIR}/git"

SRCREV = "0bc5d77ed27e0765953d93c2376a4b4aea675a01"

BPN = "gem5-aarch64-bootloader"

require gem5-aarch64-bootloader.inc
