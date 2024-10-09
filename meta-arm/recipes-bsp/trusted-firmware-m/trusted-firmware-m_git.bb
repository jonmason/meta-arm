require recipes-bsp/trusted-firmware-m/trusted-firmware-m-2.1.0-src.inc
require recipes-bsp/trusted-firmware-m/trusted-firmware-m.inc

# The required dependencies are documented in tf-m/config/config_base.cmake
SRCBRANCH_tfm = "main"
SRCREV_tfm = "d7593eb74589ec47bcf33210bfc3effe115f1266"

SRCBRANCH_tfm-extras = "main"
SRCREV_tfm-extras = "f200dc2021a1debc9b36bd16836c99f72f81278a"

SRCBRANCH_tfm-tests = "main"
SRCREV_tfm-tests = "64e8ae935f91b983036eaf37fbea386b81465fc3"

SRCBRANCH_cmsis ?= "main"
SRCREV_cmsis = "8c4dc58928b3347f6aa98b6fb2bf6770f32a72b7"

SRCBRANCH_mbedtls ?= "development"
SRCREV_mbedtls = "e21e9c33c52c91830cee31315b000c1c647e042b"

SRCBRANCH_mcuboot ?= "main"
SRCREV_mcuboot = "f1f557fd7a7f5faf19a8b37774f433ca48630b6b"

SRCBRANCH_qcbor ?= "master"
SRCREV_qcbor = "c4bded39d426ba04afd2bb0e5593ba6af7ad1226"

SRCBRANCH_tfm-psa-adac = "master"
SRCREV_tfm-psa-adac = "819a254af6fb5eefdcef194ec85d2c7627451351"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
