DEFAULTTUNE ?= "armv8-7a"

TUNEVALID[armv8-7a] = "Enable instructions for ARMv8.7-a"
TUNE_CCARGS_MARCH .= "${@bb.utils.contains('TUNE_FEATURES', 'armv8-7a', ' -march=armv8.7-a', '', d)}"
# TUNE crypto will be handled by arch-armv8a.inc below
MACHINEOVERRIDES =. "${@bb.utils.contains('TUNE_FEATURES', 'armv8-7a', 'armv8-7a:', '', d)}"

require conf/machine/include/arm/arch-armv8a.inc
require conf/machine/include/arm/feature-arm-sve.inc

# Little Endian base configs
AVAILTUNES += "armv8-7a armv8-7a-crypto armv8-7a-crypto-sve"
ARMPKGARCH:tune-armv8-7a                    ?= "armv8-7a"
ARMPKGARCH:tune-armv8-7a-crypto             ?= "armv8-7a"
ARMPKGARCH:tune-armv8-7a-crypto-sve         ?= "armv8-7a"
TUNE_FEATURES:tune-armv8-7a                  = "aarch64 armv8-7a"
TUNE_FEATURES:tune-armv8-7a-crypto           = "${TUNE_FEATURES:tune-armv8-7a} crypto"
TUNE_FEATURES:tune-armv8-7a-crypto-sve       = "${TUNE_FEATURES:tune-armv8-7a-crypto} sve"
PACKAGE_EXTRA_ARCHS:tune-armv8-7a            = "${PACKAGE_EXTRA_ARCHS:tune-armv8a} armv8-7a"
PACKAGE_EXTRA_ARCHS:tune-armv8-7a-crypto     = "${PACKAGE_EXTRA_ARCHS:tune-armv8-7a} armv8-7a-crypto"
PACKAGE_EXTRA_ARCHS:tune-armv8-7a-crypto-sve = "${PACKAGE_EXTRA_ARCHS:tune-armv8-7a-crypto} armv8-7a-crypto-sve"
BASE_LIB:tune-armv8-7a                       = "lib64"
BASE_LIB:tune-armv8-7a-crypto                = "lib64"
BASE_LIB:tune-armv8-7a-crypto-sve            = "lib64"
