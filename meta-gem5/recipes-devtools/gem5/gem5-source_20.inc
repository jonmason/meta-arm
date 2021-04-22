# gem5 sources v20.1.0.3

LIC_FILES_CHKSUM = "file://COPYING;md5=2d9514d69d8abf88b6e9125e759bf0ab \
                    file://LICENSE;md5=a585e2893cee63d16a1d8bc16c6297ec"

SRC_URI = "git://gem5.googlesource.com/public/gem5;protocol=https;nobranch=1 \
           file://pyinit-threads.patch"
RELEASE_TAG = "v20.1.0.3"
SRCREV = "cd21b5a5519940a0fa9b9a2dde68f30403d17f7e"

PV = "${RELEASE_TAG}"

S = "${WORKDIR}/git"
