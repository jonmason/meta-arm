# Kernel configuration and dts specific information

#
# Kernel configurations and dts (If not using Linux provided ones) are captured
# in this file. Update SRC_URI and do_patch for building images with custom dts
#

# We can't set FILESEXTRAPATHS once because of how the kernel classes search for
# config fragments. Discussion is ongoing as to whether this is the correct
# solution, or a workaround.
# https://bugzilla.yoctoproject.org/show_bug.cgi?id=14154
ARMBSPFILESPATHS := "${THISDIR}:${THISDIR}/files:"

# Arm platforms kmeta
SRC_URI_KMETA = "file://arm-platforms-kmeta;type=kmeta;name=arm-platforms-kmeta;destsuffix=arm-platforms-kmeta"
SRC_URI:append:fvp-base = " ${SRC_URI_KMETA}"
SRC_URI:append:fvp-base-arm32 = " ${SRC_URI_KMETA}"
SRC_URI:append:juno = " ${SRC_URI_KMETA}"
SRC_URI:append:n1sdp = " ${SRC_URI_KMETA}"
SRC_URI:append:fvp-baser-aemv8r64 = " ${SRC_URI_KMETA}"
SRCREV:arm-platforms-kmeta = "6147e82375aa9df8f2a162d42ea6406c79c854c5"

#
# Corstone-500 KMACHINE
#
COMPATIBLE_MACHINE:corstone500 = "corstone500"

#
# FVP BASE KMACHINE
#
COMPATIBLE_MACHINE:fvp-base = "fvp-base"
KMACHINE:fvp-base = "fvp"
FILESEXTRAPATHS:prepend:fvp-base := "${ARMBSPFILESPATHS}"

#
# FVP BASE ARM32 KMACHINE
#
COMPATIBLE_MACHINE:fvp-base-arm32 = "fvp-base-arm32"
KMACHINE:fvp-base-arm32 = "fvp-arm32"
FILESEXTRAPATHS:prepend:fvp-base-arm32 := "${ARMBSPFILESPATHS}"
SRC_URI:append:fvp-base-arm32 = " file://fvp-base-arm32-dts.patch \
                                  file://0001-ARM-vexpress-enable-GICv3.patch"

#
# Juno KMACHINE
#
COMPATIBLE_MACHINE:juno = "juno"
KMACHINE:juno = "juno"
KBUILD_DEFCONFIG:juno = "defconfig"
KCONFIG_MODE:juno = "--alldefconfig"
FILESEXTRAPATHS:prepend:juno := "${ARMBSPFILESPATHS}"
SRC_URI:append:juno = " \
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
COMPATIBLE_MACHINE:sgi575 = "sgi575"
KMACHINE:sgi575 = "sgi575"
KBUILD_DEFCONFIG:sgi575 = "defconfig"
KCONFIG_MODE:sgi575 = "--alldefconfig"

#
# Total Compute KMACHINE
#
COMPATIBLE_MACHINE:tc0 = "tc0"
KMACHINE:tc0 = "tc0"
KCONFIG_MODE:tc0 = "--alldefconfig"
FILESEXTRAPATHS:prepend:tc0 := "${ARMBSPFILESPATHS}"
SRC_URI:append:tc0 = " \
    file://defconfig \
    file://0001-drm-Add-component-aware-simple-encoder.patch \
    file://0002-drm-arm-komeda-add-RENDER-capability-to-the-device-n.patch \
    file://0003-Adapt-ION-interface-to-match-Android.patch \
    file://0004-dt-bindings-mailbox-arm-mhuv2-Add-bindings.patch \
    file://0005-mailbox-arm_mhuv2-Add-driver.patch \
    file://0006-mailbox-arm_mhuv2-Fix-sparse-warnings.patch \
    file://0007-mailbox-arm_mhuv2-make-remove-callback-return-void.patch \
    file://0008-mailbox-arm_mhuv2-Skip-calling-kfree-with-invalid-po.patch \
    file://0009-arm64-smccc-Add-support-for-SMCCCv1.2-extended-input.patch \
    file://0010-firmware-arm_ffa-Add-initial-FFA-bus-support-for-dev.patch \
    file://0011-firmware-arm_ffa-Add-initial-Arm-FFA-driver-support.patch \
    file://0012-firmware-arm_ffa-Add-support-for-SMCCC-as-transport-.patch \
    file://0013-firmware-arm_ffa-Setup-in-kernel-users-of-FFA-partit.patch \
    file://0014-firmware-arm_ffa-Add-support-for-MEM_-interfaces.patch \
    file://0015-tee-add-sec_world_id-to-struct-tee_shm.patch \
    file://0016-optee-simplify-optee_release.patch \
    file://0017-optee-sync-OP-TEE-headers.patch \
    file://0018-optee-refactor-driver-with-internal-callbacks.patch \
    file://0019-optee-add-a-FF-A-memory-pool.patch \
    file://0020-optee-add-FF-A-support.patch \
    file://0021-drivers-optee-hack-for-UUID-endianess-issue.patch \
    "

#
# N1SDP KMACHINE
#
FILESEXTRAPATHS:prepend:n1sdp := "${THISDIR}/linux-yocto-5.10/n1sdp:"
COMPATIBLE_MACHINE:n1sdp = "n1sdp"
KBUILD_DEFCONFIG:n1sdp = "defconfig"
KCONFIG_MODE:n1sdp = "--alldefconfig"
FILESEXTRAPATHS:prepend:n1sdp := "${ARMBSPFILESPATHS}"
SRC_URI:append:n1sdp = " \
    file://0001-pci_quirk-add-acs-override-for-PCI-devices.patch \
    file://0002-pcie-Add-quirk-for-the-Arm-Neoverse-N1SDP-platform.patch \
    file://0003-n1sdp-update-n1sdp-pci-quirk-for-SR-IOV-support.patch \
    file://0004-n1sdp-pcie-add-quirk-support-enabling-remote-chip-PC.patch \
    file://0005-r8169-Fix-to-avoid-duplicate-sysfs-entry-creation-er.patch \
    file://0001-arm64-defconfig-drop-unused-BACKLIGHT_GENERIC-option.patch \
    file://no-power-avs.patch \
    file://enable-realtek-R8169.cfg \
    file://enable-usb_conn_gpio.cfg \
    "
# Since we use the intree defconfig and the preempt-rt turns off some configs
# do_kernel_configcheck will display warnings. So, lets disable it.
KCONF_AUDIT_LEVEL:n1sdp:pn-linux-yocto-rt = "0"

#
# Musca B1/S2 can't run Linux
#
COMPATIBLE_MACHINE:musca-b1 = "(^$)"
COMPATIBLE_MACHINE:musca-s1 = "(^$)"

#
# FVP BaseR AEMv8r64 Machine
#
COMPATIBLE_MACHINE:fvp-baser-aemv8r64 = "fvp-baser-aemv8r64"
FILESEXTRAPATHS:prepend:fvp-baser-aemv8r64 := "${ARMBSPFILESPATHS}"
SRC_URI:append:fvp-baser-aemv8r64 = " file://fvp-baser-aemv8r64.dts;subdir=git/arch/arm64/boot/dts/arm"
