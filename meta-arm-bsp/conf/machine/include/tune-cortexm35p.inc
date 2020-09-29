#
# Tune Settings for Cortex-M35P
#
DEFAULTTUNE ?= "cortexm33p"

TUNEVALID[cortexm35p] = "Enable Cortex-M35p specific processor optimizations"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'cortexm35p', ' -mcpu=cortex-m35p', '', d)}"

require conf/machine/include/arm/arch-armv8m-main.inc


AVAILTUNES                          += "cortexm35p"
ARMPKGARCH_tune-cortexm35p           = "cortexm35p"
TUNE_FEATURES_tune-cortexm35p        = "${TUNE_FEATURES_tune-armv8m-main} cortexm35p"
PACKAGE_EXTRA_ARCHS_tune-cortexm35p  = "${PACKAGE_EXTRA_ARCHS_tune-armv8m-main} cortexm35p"
