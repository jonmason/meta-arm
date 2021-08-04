DEFAULTTUNE ?= "armv8r"

TUNEVALID[armv8r] = "Enable instructions for ARMv8-r"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'armv8r', ' -march=armv8-r', '', d)}"
TUNEVALID[crc] = "Enable instructions for ARMv8-r Cyclic Redundancy Check (CRC)"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'crc', '+crc', '', d)}"
TUNEVALID[crypto] = "Enable instructions for ARMv8-r cryptographic"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'crypto', '+crypto', '', d)}"
MACHINEOVERRIDES =. "${@bb.utils.contains('TUNE_FEATURES', 'armv8r', 'armv8-r:', '', d)}"

require conf/machine/include/arm/arch-arm64.inc

# Little Endian base configs
AVAILTUNES += "armv8r armv8r-crc armv8r-crypto"
ARMPKGARCH:tune-armv8r                    ?= "armv8r"
ARMPKGARCH:tune-armv8r-crc                ?= "armv8r"
ARMPKGARCH:tune-armv8r-crypto             ?= "armv8r"
TUNE_FEATURES:tune-armv8r                  = "aarch64 armv8r"
TUNE_FEATURES:tune-armv8r-crc              = "${TUNE_FEATURES:tune-armv8r} crc"
TUNE_FEATURES:tune-armv8r-crypto           = "${TUNE_FEATURES:tune-armv8r} crypto"
PACKAGE_EXTRA_ARCHS:tune-armv8r            = "aarch64 armv8r"
PACKAGE_EXTRA_ARCHS:tune-armv8r-crc        = "${PACKAGE_EXTRA_ARCHS:tune-armv8r} armv8r-crc"
PACKAGE_EXTRA_ARCHS:tune-armv8r-crypto     = "${PACKAGE_EXTRA_ARCHS:tune-armv8r} armv8r-crypto"
BASE_LIB:tune-armv8r                       = "lib64"
BASE_LIB:tune-armv8r-crc                   = "lib64"
BASE_LIB:tune-armv8r-crypto                = "lib64"
