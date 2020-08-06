# Kernel configuration and dts specific information

#
# Kernel configurations and dts (If not using Linux provided ones) are captured
# in this file. Update SRC_URI and do_patch for building images with custom dts
#

FILESEXTRAPATHS_prepend := "${THISDIR}:${THISDIR}/files:"

# Arm platforms kmeta
SRC_URI += "file://arm-platforms-kmeta;type=kmeta;name=arm-platforms-kmeta;destsuffix=arm-platforms-kmeta"

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
SRC_URI_append_gem5-arm64 = " file://dts/gem5-arm64;subdir=add-files"

do_patch_append_gem5-arm64() {
    tar -C ${WORKDIR}/add-files/dts -cf - gem5-arm64 | \
        tar -C arch/arm64/boot/dts -xf -
}
