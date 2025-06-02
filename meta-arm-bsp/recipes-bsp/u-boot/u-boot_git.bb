require recipes-bsp/u-boot/u-boot-common.inc
require recipes-bsp/u-boot/u-boot.inc

DEPENDS += "bc-native dtc-native gnutls-native python3-pyelftools-native"

# v2025.07 tag
SRCREV = "e37de002fac3895e8d0b60ae2015e17bb33e2b5b"
SRC_URI = "git://source.denx.de/u-boot/u-boot.git;protocol=https;branch=master"
PV .= "+git"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
