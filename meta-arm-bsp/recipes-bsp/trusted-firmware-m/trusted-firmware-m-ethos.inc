# Ethos-U Core Driver 25.05, from lib/ext/ethos_u_core_driver/CMakeLists.txt.
SRC_URI_TRUSTED_FIRMWARE_M_ETHOS_DRIVER ?= "git://git.gitlab.arm.com/artificial-intelligence/ethos-u/ethos-u-core-driver.git;protocol=https"
SRCREV_ethos-driver = "60b4fbf76af8bff11c316588e77b7d626ab65e75"

SRC_URI:append = " ${SRC_URI_TRUSTED_FIRMWARE_M_ETHOS_DRIVER};branch=main;name=ethos-driver;destsuffix=tfm/external/ethos_u_core_driver"
SRCREV_FORMAT:append = "_ethos-driver"
EXTRA_OECMAKE:append = " -DETHOS_DRIVER_PATH=${S}/external/ethos_u_core_driver"
