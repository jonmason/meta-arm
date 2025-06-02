require recipes-bsp/u-boot/u-boot-common.inc
require recipes-bsp/u-boot/u-boot.inc

DEPENDS += "bc-native dtc-native gnutls-native python3-pyelftools-native"

# v2025.10-rc4 tag
SRCREV = "7a4f3c5652157cbb3d26a7728bfe537ea483efc9"
SRC_URI = "git://source.denx.de/u-boot/u-boot.git;protocol=https;branch=master"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
