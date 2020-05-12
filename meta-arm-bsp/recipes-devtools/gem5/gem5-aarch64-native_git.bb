# gem5 simulator source and checksum information

LIC_FILES_CHKSUM = "file://COPYING;md5=2d9514d69d8abf88b6e9125e759bf0ab \
                    file://LICENSE;md5=a585e2893cee63d16a1d8bc16c6297ec"

# The recipe is currently using a version in the release staging branch of gem5
# until version 20 is released
SRC_URI = "git://gem5.googlesource.com/public/gem5;protocol=https;branch=release-staging-v20.0.0.0"

PV = "git${SRCPV}"

S = "${WORKDIR}/git"

SRCREV = "0bc5d77ed27e0765953d93c2376a4b4aea675a01"

BPN = "gem5-aarch64-native"

require gem5-aarch64-native.inc
require gem5-native.inc

do_compile_prepend() {
    # Gem5 expect to have python in the path (can be python2 or 3)
    # Create a link named python to python3
    real=$(which ${PYTHON})
    ln -snf $real $(dirname $real)/python
}
