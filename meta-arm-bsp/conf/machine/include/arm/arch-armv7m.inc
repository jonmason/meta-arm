#
# Tune Settings for Cortex-M3
#
TUNEVALID[cortexm3] = "Enable Cortex-M3 specific processor optimizations"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'cortexm3', ' -mcpu=cortex-m3', '', d)}"


AVAILTUNES                            += "cortexm3"
ARMPKGARCH_tune-cortexm3               = "cortexm3"
TUNE_FEATURES_tune-cortexm3            = "${TUNE_FEATURES_tune-armv7m} cortexm3"
PACKAGE_EXTRA_ARCHS_tune-cortexm3      = "${PACKAGE_EXTRA_ARCHS_tune-armv7m} cortexm3"

#
# Defaults for ARMv7-m
#
DEFAULTTUNE ?= "armv7m"

TUNEVALID[armv7m] = "Enable instructions for ARMv7-m"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'armv7m', ' -march=armv7-m', '', d)}"
MACHINEOVERRIDES =. "${@bb.utils.contains('TUNE_FEATURES', 'armv7m', 'armv7m:', '', d)}"

TUNECONFLICTS[armv7m] = "armv4 armv5 armv6 armv7a"

require conf/machine/include/arm/arch-armv6m.inc


AVAILTUNES                            += "armv7m"
ARMPKGARCH_tune-armv7m                 = "armv7m"
TUNE_FEATURES_tune-armv7m              = "armv7m"
PACKAGE_EXTRA_ARCHS_tune-armv7m        = "armv7m"
