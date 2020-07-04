# Kernel configuration and dts specific information

#
# Kernel configurations and dts (If not using Linux provided ones) are captured
# in this file. Update SRC_URI and do_patch for building images with custom dts
#

FILESEXTRAPATHS_prepend := "${THISDIR}:${THISDIR}/files:"

# Arm platforms kmeta
SRC_URI_KMETA = "file://arm-platforms-kmeta;type=kmeta;name=arm-platforms-kmeta;destsuffix=arm-platforms-kmeta"
SRC_URI_append_foundation-armv8 = " ${SRC_URI_KMETA}"
SRC_URI_append_fvp-base = " ${SRC_URI_KMETA}"
SRC_URI_append_juno = " ${SRC_URI_KMETA}"
SRC_URI_append_gem5-arm64 = " ${SRC_URI_KMETA}"
SRCREV_arm-platforms-kmeta = "6147e82375aa9df8f2a162d42ea6406c79c854c5"

#
# Cortex-A5 DesignStart KMACHINE
#
COMPATIBLE_MACHINE_a5ds = "a5ds"
KMACHINE_a5ds = "a5ds"

#
# FVP FOUNDATION KMACHINE
#
COMPATIBLE_MACHINE_foundation-armv8 = "foundation-armv8"
KMACHINE_foundation-armv8 = "fvp"

#
# FVP BASE KMACHINE
#
COMPATIBLE_MACHINE_fvp-base = "fvp-base"
KMACHINE_fvp-base = "fvp"
SRC_URI_append_fvp-base = " file://fvp-base-dts.patch"

#
# Juno KMACHINE
#
COMPATIBLE_MACHINE_juno = "juno"
KMACHINE_juno = "juno"

#
# Gem5 arm64 KMACHINE
#
COMPATIBLE_MACHINE_gem5-arm64 = "gem5-arm64"
KMACHINE_gem5-arm64 = "gem5-arm64"
SRC_URI_append_gem5-arm64 = " file://gem5-dts.patch"
