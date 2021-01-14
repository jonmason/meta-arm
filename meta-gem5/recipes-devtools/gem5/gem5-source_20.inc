# gem5 sources v20.0.0.3

LIC_FILES_CHKSUM = "file://COPYING;md5=2d9514d69d8abf88b6e9125e759bf0ab \
                    file://LICENSE;md5=a585e2893cee63d16a1d8bc16c6297ec"

SRC_URI = "git://gem5.googlesource.com/public/gem5;protocol=https;nobranch=1"
RELEASE_TAG = "v20.0.0.3"
SRCREV = "fa70478413e4650d0058cbfe81fd5ce362101994"

PV = "${RELEASE_TAG}"

S = "${WORKDIR}/git"
