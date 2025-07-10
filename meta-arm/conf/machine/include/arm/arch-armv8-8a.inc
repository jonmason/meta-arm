DEFAULTTUNE ?= "armv8-8a"

TUNEVALID[armv8-8a] = "Enable instructions for ARMv8.8-a"
TUNE_CCARGS_MARCH .= "${@bb.utils.contains('TUNE_FEATURES', 'armv8-8a', ' -march=armv8.8-a', '', d)}"
# TUNE crypto will be handled by arch-armv8a.inc below
MACHINEOVERRIDES =. "${@bb.utils.contains('TUNE_FEATURES', 'armv8-8a', 'armv8-8a:', '', d)}"

require conf/machine/include/arm/arch-armv8a.inc
require conf/machine/include/arm/feature-arm-sve.inc

# Little Endian base configs
AVAILTUNES += "armv8-8a armv8-8a-crypto armv8-8a-crypto-sve"
ARMPKGARCH:tune-armv8-8a                    ?= "armv8-8a"
ARMPKGARCH:tune-armv8-8a-crypto             ?= "armv8-8a"
ARMPKGARCH:tune-armv8-8a-crypto-sve         ?= "armv8-8a"
TUNE_FEATURES:tune-armv8-8a                  = "aarch64 armv8-8a"
TUNE_FEATURES:tune-armv8-8a-crypto           = "${TUNE_FEATURES:tune-armv8-8a} crypto"
TUNE_FEATURES:tune-armv8-8a-crypto-sve       = "${TUNE_FEATURES:tune-armv8-8a-crypto} sve"
PACKAGE_EXTRA_ARCHS:tune-armv8-8a            = "${PACKAGE_EXTRA_ARCHS:tune-armv8a} armv8-8a"
PACKAGE_EXTRA_ARCHS:tune-armv8-8a-crypto     = "${PACKAGE_EXTRA_ARCHS:tune-armv8-8a} armv8-8a-crypto"
PACKAGE_EXTRA_ARCHS:tune-armv8-8a-crypto-sve = "${PACKAGE_EXTRA_ARCHS:tune-armv8-8a-crypto} armv8-8a-crypto-sve"
BASE_LIB:tune-armv8-8a                       = "lib64"
BASE_LIB:tune-armv8-8a-crypto                = "lib64"
BASE_LIB:tune-armv8-8a-crypto-sve            = "lib64"
