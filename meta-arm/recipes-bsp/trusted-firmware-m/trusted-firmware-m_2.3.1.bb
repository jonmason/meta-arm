require recipes-bsp/trusted-firmware-m/trusted-firmware-m-${PV}-src.inc
require recipes-bsp/trusted-firmware-m/trusted-firmware-m.inc

DEPENDS += "trusted-firmware-m-scripts-native"

TFM_TESTIMAGE_AUTO ?= "0"
do_build[depends] += "${@bb.utils.contains('TFM_TESTIMAGE_AUTO', '1', 'trusted-firmware-m-tests:do_testimage', '', d)}"

# FIXME - arm-none-eabi/bin/ld: error: unsupported option: -z relro
# Working around the issue by removing the loader flags, which aren't relevant for us here
# Long term fix, create a baremetal firmware bbclass that doesn't add this stuff
SECURITY_LDFLAGS = ""
