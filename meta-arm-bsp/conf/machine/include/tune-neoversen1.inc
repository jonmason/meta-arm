DEFAULTTUNE ?= "neoversen1"

TUNEVALID[neoversen1] = "Enable Neoverse-N1 specific processor optimizations"
# Note: Neoverse was called Ares, and GCC will accept "ares" in place of "neoverse-n1"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'neoversen1', ' -mcpu=neoverse-n1', '', d)}"

require conf/machine/include/arm/arch-armv8-2a.inc

# Little Endian base configs
AVAILTUNES += "neoversen1"
ARMPKGARCH_tune-neoversen1             = "neoversen1"
TUNE_FEATURES_tune-neoversen1          = "aarch64 neoversen1 crc crypto"
PACKAGE_EXTRA_ARCHS_tune-neoversen1    = "${PACKAGE_EXTRA_ARCHS_tune-armv8a-crc-crypto} neoversen1"
BASE_LIB_tune-neoversen1               = "lib64"
