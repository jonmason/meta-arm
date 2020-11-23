# Kernel configuration and dts specific information

#
# Kernel configurations and dts (If not using Linux provided ones) are captured
# in this file. Update SRC_URI and do_patch for building images with custom dts
#

FILESEXTRAPATHS_prepend := "${THISDIR}:${THISDIR}/files:"

# Arm platforms kmeta
SRC_URI_KMETA = "file://arm-platforms-kmeta;type=kmeta;name=arm-platforms-kmeta;destsuffix=arm-platforms-kmeta"
SRC_URI_append_fvp-base = " ${SRC_URI_KMETA}"
SRC_URI_append_fvp-base-arm32 = " ${SRC_URI_KMETA}"
SRC_URI_append_juno = " ${SRC_URI_KMETA}"
SRC_URI_append_sgi575 = " ${SRC_URI_KMETA}"
SRC_URI_append_gem5-arm64 = " ${SRC_URI_KMETA}"
SRCREV_arm-platforms-kmeta = "6147e82375aa9df8f2a162d42ea6406c79c854c5"

#
# Corstone-500 KMACHINE
#
COMPATIBLE_MACHINE_corstone500 = "corstone500"

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
SRC_URI_append_fvp-base-arm32 = " file://fvp-base-arm32-dts.patch \
                                  file://0001-ARM-vexpress-enable-GICv3.patch"

#
# Juno KMACHINE
#
COMPATIBLE_MACHINE_juno = "juno"
KMACHINE_juno = "juno"
KBUILD_DEFCONFIG_juno = "defconfig"
KCONFIG_MODE_juno = "--alldefconfig"
SRC_URI_append_juno = " \
    file://0001-mailbox-add-support-for-doorbell-signal-mode-control.patch \
    file://0002-dt-bindings-mailbox-add-bindings-to-support-ARM-MHU-.patch \
    file://0003-mailbox-arm_mhu-migrate-to-threaded-irq-handler.patch \
    file://0004-mailbox-arm_mhu-re-factor-data-structure-to-add-door.patch \
    file://0005-mailbox-arm_mhu-add-full-support-for-the-doorbells.patch \
    file://0006-mailbox-arm_mhu-add-support-to-read-and-record-mbox-.patch \
    file://0007-arm64-defconfig-add-all-SCMI-related-configs.patch \
    file://0008-arm64-dts-juno-add-mhu-doorbell-support-and-scmi-dev.patch \
    "

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
KCONFIG_MODE_tc0 = "--alldefconfig"
SRC_URI_append_tc0 = " \
    file://defconfig \
    file://0001-drm-Add-component-aware-simple-encoder.patch \
    file://0002-drm-arm-komeda-add-RENDER-capability-to-the-device-n.patch \
    file://0003-mailbox-arm_mhuv2-add-device-tree-binding-documentat.patch \
    file://0004-mailbox-arm_mhuv2-add-arm-mhuv2-driver.patch \
    file://0005-mailbox-arm_mhuv2-add-doorbell-transport-protocol-op.patch \
    file://0006-mailbox-arm_mhuv2-add-multi-word-transport-protocol-.patch \
    file://0007-firmware-arm_scmi-Add-fast_switch_possible-api.patch \
    file://0008-cpufreq-arm_scmi-Set-fast_switch_possible-conditiona.patch \
    "

