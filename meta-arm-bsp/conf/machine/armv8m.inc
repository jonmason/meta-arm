DEFAULTTUNE ?= "armv8m"

TUNEVALID[armv8m] = "Enable instructions for ARMv8-m"
AVAILTUNES += "armv8m"

ARMPKGARCH_tune-armv8m ?= "armv8m"
TUNE_FEATURES_tune-armv8m = "armv8m"
PACKAGE_EXTRA_ARCHS_tune-armv8m = "armv8m"

require conf/machine/include/arm/arch-arm.inc
