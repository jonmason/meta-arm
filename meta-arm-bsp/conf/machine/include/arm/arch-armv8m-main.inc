#
#
# Defaults for ARMv8-M.main
#
DEFAULTTUNE ?= "armv8m-main"

TUNEVALID[armv8m-main] = "Enable instructions for ARMv8-m.main"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'armv8m-main', ' -march=armv8-m.main', '', d)}"
MACHINEOVERRIDES =. "${@bb.utils.contains('TUNE_FEATURES', 'armv8m-main', 'armv8m-main:', '', d)}"

TUNECONFLICTS[armv8m-main] = "armv4 armv5 armv6 armv7a"

require conf/machine/include/arm/arch-armv8m-base.inc


AVAILTUNES                          += "armv8m-main"
ARMPKGARCH_tune-armv8m-main          = "armv8m-main"
TUNE_FEATURES_tune-armv8m-main       = "armv8m-main"
PACKAGE_EXTRA_ARCHS_tune-armv8m-main = "armv8m-main"
