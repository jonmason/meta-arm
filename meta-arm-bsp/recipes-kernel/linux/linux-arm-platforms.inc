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
SRC_URI_append_fvp-base-arm32 = " ${SRC_URI_KMETA}"
SRC_URI_append_juno = " ${SRC_URI_KMETA}"
SRC_URI_append_sgi575 = " ${SRC_URI_KMETA}"
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
# FVP BASE ARM32 KMACHINE
#
COMPATIBLE_MACHINE_fvp-base-arm32 = "fvp-base-arm32"
KMACHINE_fvp-base-arm32 = "fvp-arm32"
SRC_URI_append_fvp-base-arm32 = " file://fvp-base-arm32-dts.patch"

#
# Juno KMACHINE
#
COMPATIBLE_MACHINE_juno = "juno"
KMACHINE_juno = "juno"

#
# SGI575 KMACHINE
#
COMPATIBLE_MACHINE_sgi575 = "sgi575"
KMACHINE_sgi575 = "sgi575"
KBUILD_DEFCONFIG_sgi575 = "defconfig"
KCONFIG_MODE_sgi575 = "--alldefconfig"

#
# Total Compute KMACHINE
#
COMPATIBLE_MACHINE_tc0 = "tc0"
KMACHINE_tc0 = "tc0"
KBUILD_DEFCONFIG_tc0 = "defconfig"
KCONFIG_MODE_tc0 = "--alldefconfig"
SRC_URI_append_tc0 = " \
    file://0001-drm-Add-component-aware-simple-encoder.patch \
    file://0002-swap-red-and-blue-colors-in-HDLCD-driver.patch \
    file://defconfig \
    "
