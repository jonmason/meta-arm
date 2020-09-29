#
# Tune Settings for Cortex-M33
#
DEFAULTTUNE ?= "armv8m"

TUNEVALID[armv8m] = "Enable instructions for ARMv8-m"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'armv8m', ' -march=armv7-m', '', d)}"

require conf/machine/include/arm/arch-armv8m-main.inc

AVAILTUNES += "armv8m"
ARMPKGARCH_tune-armv8m ?= "armv8m"
TUNE_FEATURES_tune-armv8m = "armv8m"
PACKAGE_EXTRA_ARCHS_tune-armv8m = "armv8m"

