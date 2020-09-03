DEFAULTTUNE ?= "cortexa75-cortexa55"

TUNEVALID[cortexa75-cortexa55] = "Enable big.LITTLE Cortex-A75.Cortex-A55 specific processor optimizations"
TUNECONFLICTS[aarch64] = "armv4 armv5 armv6 armv7 armv7a"
MACHINEOVERRIDES =. "${@bb.utils.contains("TUNE_FEATURES", "cortexa75-cortexa55", "cortexa75-cortexa55:", "" ,d)}"
TUNE_CCARGS .= "${@bb.utils.contains("TUNE_FEATURES", "cortexa75-cortexa55", " -mcpu=cortex-a75.cortex-a55", "", d)}"

require conf/machine/include/arm/arch-armv8-2a.inc

# cortexa75.cortexa55 implies crc support
AVAILTUNES += "cortexa75-cortexa55 cortexa75-cortexa55-crypto"
ARMPKGARCH_tune-cortexa75-cortexa55                  = "cortexa75-cortexa55"
ARMPKGARCH_tune-cortexa75-cortexa55-crypto           = "cortexa75-cortexa55-crypto"
TUNE_FEATURES_tune-cortexa75-cortexa55               = "aarch64 crc cortexa75-cortexa55"
TUNE_FEATURES_tune-cortexa75-cortexa55-crypto        = "aarch64 crc crypto cortexa75-cortexa55"
PACKAGE_EXTRA_ARCHS_tune-cortexa75-cortexa55         = "${PACKAGE_EXTRA_ARCHS_tune-armv8a-crc}        cortexa75-cortexa55"
PACKAGE_EXTRA_ARCHS_tune-cortexa75-cortexa55-crypto  = "${PACKAGE_EXTRA_ARCHS_tune-armv8a-crc-crypto} cortexa75-cortexa55 cortexa75-cortexa55-crypto"
BASE_LIB_tune-cortexa75-cortexa55                    = "lib64"
BASE_LIB_tune-cortexa75-cortexa55-crypto             = "lib64"

