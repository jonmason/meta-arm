#
# Defaults for ARMv7-r
#
DEFAULTTUNE ?= "armv7r"

TUNEVALID[armv7r] = "Enable instructions for ARMv7-r"
TUNE_CCARGS_MARCH = "${@bb.utils.contains('TUNE_FEATURES', 'armv7r', ' -march=armv7-r', '', d)}"
MACHINEOVERRIDES =. "${@bb.utils.contains('TUNE_FEATURES', 'armv7r', 'armv7r:', '', d)}"

TUNECONFLICTS[armv7r] = "armv4 armv5 armv6 armv7a"

require conf/machine/include/arm/arch-armv6.inc
require conf/machine/include/arm/feature-arm-idiv.inc
require conf/machine/include/arm/feature-arm-neon.inc

AVAILTUNES                            += "armv7r armv7r-vfpv3d16"
ARMPKGARCH:tune-armv7r                 = "armv7r"
ARMPKGARCH:tune-armv7r-vfpv3d16        = "armv7r"
TUNE_FEATURES:tune-armv7r              = "armv7r"
TUNE_FEATURES:tune-armv7r-vfpv3d16     = "${TUNE_FEATURES:tune-armv7r} vfpv3d16"
PACKAGE_EXTRA_ARCHS:tune-armv7r        = "armv7r"
PACKAGE_EXTRA_ARCHS:tune-armv7r-vfpv3d16  = "${PACKAGE_EXTRA_ARCHS:tune-armv7r} tune-armv7r-fpv3d16"

# FIXME - This goes in arch-arm.inc when upstreamed
# Some -march settings need a +X option passed in.  Since we cannot guarantee that any specified TUNE_CCARGS option is set in any order, we must hard code the order here to allow for it.
TUNE_CCARGS_MARCH_OPTS ??= ""
TUNE_CCARGS .= "${TUNE_CCARGS_MARCH}${TUNE_CCARGS_MARCH_OPTS}"

# FIXME - Thise goes in feature-arm-neon.inc when upstreamed
TUNE_CCARGS_MARCH_OPTS .= "${@bb.utils.contains('TUNE_FEATURES', [ 'vfpv3d16', 'vfpv5spd16' ], '+fp', '', d)}"
