# Kernel configuration and dts specific information

#
# Kernel configurations and dts (If not using Linux provided ones) are captured
# in this file. Update SRC_URI and do_patch for building images with custom dts
#

FILESEXTRAPATHS_prepend := "${THISDIR}:${THISDIR}/files:"

# Arm platforms kmeta
SRC_URI_append = " file://arm-platforms-kmeta;type=kmeta;name=arm-platforms-kmeta;destsuffix=arm-platforms-kmeta"

#
# FVP FOUNDATION KMACHINE
#
COMPATIBLE_MACHINE_foundation-armv8 = "foundation-armv8"
KMACHINE_foundation-armv8 = "fvp"

