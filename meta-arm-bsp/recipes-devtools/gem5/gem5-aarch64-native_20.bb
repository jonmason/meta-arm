# gem5 simulator source and checksum information

LIC_FILES_CHKSUM = "file://COPYING;md5=2d9514d69d8abf88b6e9125e759bf0ab \
                    file://LICENSE;md5=a585e2893cee63d16a1d8bc16c6297ec"

SRC_URI = "git://gem5.googlesource.com/public/gem5;protocol=https;nobranch=1 \
           file://0001-scons-Add-MARSHAL_XXFLAGS_EXTRA-for-the-marshal-object.patch \
           file://0002-arch-arm-Introduce-HavePACExt-helper.patch \
           file://0003-arch-arm-Check-if-PAC-is-implemented-before-executing-insts.patch \
          "
RELEASE_TAG = "v20.0.0.1"
SRCREV = "332a9de33db603e0aefedae1e05134db4257ea3e"

PV = "${RELEASE_TAG}"

S = "${WORKDIR}/git"

BPN = "gem5-aarch64-native"

require gem5-aarch64-native.inc
require gem5-native.inc

# Get rid of compiler errors when building protobuf
GEM5_SCONS_ARGS_append = " CCFLAGS_EXTRA='-Wno-error=unused-variable -Wno-error=array-bounds -Wno-error=parentheses -Wno-type-limits' --verbose"

# Get rid of linker errors and have a faster link process
GEM5_SCONS_ARGS_append = " LDFLAGS_EXTRA='${BUILD_LDFLAGS}' \
MARSHAL_LDFLAGS_EXTRA='${BUILD_LDFLAGS}' --force-lto "

do_compile_prepend() {
    # Gem5 expect to have python in the path (can be python2 or 3)
    # Create a link named python to python3
    real=$(which ${PYTHON})
    ln -snf $real $(dirname $real)/python
}
