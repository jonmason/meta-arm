require recipes-bsp/u-boot/u-boot-common.inc
require recipes-bsp/u-boot/u-boot.inc

DEPENDS += "bc-native dtc-native gnutls-native python3-pyelftools-native"

# v2025.04 tag
SRCREV = "34820924edbc4ec7803eb89d9852f4b870fa760a"
SRC_URI = "git://source.denx.de/u-boot/u-boot.git;protocol=https;branch=master"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
