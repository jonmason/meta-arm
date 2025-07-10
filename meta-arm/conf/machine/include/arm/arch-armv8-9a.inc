DEFAULTTUNE ?= "armv8-9a"

TUNEVALID[armv8-9a] = "Enable instructions for ARMv8.9-a"
TUNE_CCARGS_MARCH .= "${@bb.utils.contains('TUNE_FEATURES', 'armv8-9a', ' -march=armv8.9-a', '', d)}"
# TUNE crypto will be handled by arch-armv8a.inc below
MACHINEOVERRIDES =. "${@bb.utils.contains('TUNE_FEATURES', 'armv8-9a', 'armv8-9a:', '', d)}"

require conf/machine/include/arm/arch-armv8a.inc
require conf/machine/include/arm/feature-arm-sve.inc

# Little Endian base configs
AVAILTUNES += "armv8-9a armv8-9a-crypto armv8-9a-crypto-sve"
ARMPKGARCH:tune-armv8-9a                    ?= "armv8-9a"
ARMPKGARCH:tune-armv8-9a-crypto             ?= "armv8-9a"
ARMPKGARCH:tune-armv8-9a-crypto-sve         ?= "armv8-9a"
TUNE_FEATURES:tune-armv8-9a                  = "aarch64 armv8-9a"
TUNE_FEATURES:tune-armv8-9a-crypto           = "${TUNE_FEATURES:tune-armv8-9a} crypto"
TUNE_FEATURES:tune-armv8-9a-crypto-sve       = "${TUNE_FEATURES:tune-armv8-9a-crypto} sve"
PACKAGE_EXTRA_ARCHS:tune-armv8-9a            = "${PACKAGE_EXTRA_ARCHS:tune-armv8a} armv8-9a"
PACKAGE_EXTRA_ARCHS:tune-armv8-9a-crypto     = "${PACKAGE_EXTRA_ARCHS:tune-armv8-9a} armv8-9a-crypto"
PACKAGE_EXTRA_ARCHS:tune-armv8-9a-crypto-sve = "${PACKAGE_EXTRA_ARCHS:tune-armv8-9a-crypto} armv8-9a-crypto-sve"
BASE_LIB:tune-armv8-9a                       = "lib64"
BASE_LIB:tune-armv8-9a-crypto                = "lib64"
BASE_LIB:tune-armv8-9a-crypto-sve            = "lib64"
