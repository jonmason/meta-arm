require recipes-bsp/u-boot/u-boot-common.inc
require recipes-bsp/u-boot/u-boot.inc

DEPENDS += "bc-native dtc-native gnutls-native python3-pyelftools-native"

SRCREV = "34820924edbc4ec7803eb89d9852f4b870fa760a"
SRC_URI = "git://source.denx.de/u-boot/u-boot.git;protocol=https;branch=master"
