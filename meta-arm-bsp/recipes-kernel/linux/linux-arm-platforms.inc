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
SRC_URI:append:fvp-baser-aemv8r64 = " ${SRC_URI_KMETA}"
SRC_URI:append:juno = " ${SRC_URI_KMETA}"
SRC_URI:append:n1sdp = " ${SRC_URI_KMETA}"
SRC_URI:append:tc = " ${SRC_URI_KMETA}"
SRCREV:arm-platforms-kmeta = "6147e82375aa9df8f2a162d42ea6406c79c854c5"

#
# Corstone-500 KMACHINE
#
COMPATIBLE_MACHINE:corstone500 = "corstone500"
KBUILD_DEFCONFIG:corstone500  = "multi_v7_defconfig"
KCONFIG_MODE:corstone500 = "--alldefconfig"

#
# Corstone1000 KMACHINE
#
FILESEXTRAPATHS:prepend:corstone1000 := "${ARMBSPFILESPATHS}"
COMPATIBLE_MACHINE:corstone1000 = "${MACHINE}"
KCONFIG_MODE:corstone1000 = "--alldefconfig"
KMACHINE:corstone1000 = "corstone1000"
LINUX_KERNEL_TYPE:corstone1000 = "standard"
#disabling the rootfs cpio file compression so it is not compressed twice when bundled with the kernel
KERNEL_EXTRA_ARGS:corstone1000 += "CONFIG_INITRAMFS_COMPRESSION_NONE=y"
SRC_URI:append:corstone1000 = " \
           file://0001-arm64-Correct-wrong-label-in-macro-__init_el2_gicv3.patch \
           file://defconfig  \
        "

SRC_URI:append:corstone1000 = " ${@bb.utils.contains('MACHINE_FEATURES', \
                                                            'corstone1000_kernel_debug', \
                                                            'file://corstone1000_kernel_debug.cfg', \
                                                            '', \
                                                             d)}"

# Default kernel features not needed for corstone1000
# otherwise the extra kernel modules will increase the rootfs size
# corstone1000 has limited flash memory constraints
KERNEL_EXTRA_FEATURES:corstone1000 = ""
KERNEL_FEATURES:corstone1000 = ""

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
# FVP BaseR AEMv8r64 Machine
#
COMPATIBLE_MACHINE:fvp-baser-aemv8r64 = "fvp-baser-aemv8r64"
FILESEXTRAPATHS:prepend:fvp-baser-aemv8r64 := "${ARMBSPFILESPATHS}"
SRC_URI:append:fvp-baser-aemv8r64 = " file://fvp-baser-aemv8r64.dts;subdir=git/arch/arm64/boot/dts/arm"

#
# Juno KMACHINE
#
COMPATIBLE_MACHINE:juno = "juno"
KBUILD_DEFCONFIG:juno = "defconfig"
KCONFIG_MODE:juno = "--alldefconfig"
FILESEXTRAPATHS:prepend:juno := "${ARMBSPFILESPATHS}"
SRC_URI:append:juno = " file://juno-dts-mhu-doorbell.patch"

#
# Musca B1/S2 can't run Linux
#
COMPATIBLE_MACHINE:musca-b1 = "(^$)"
COMPATIBLE_MACHINE:musca-s1 = "(^$)"

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
    file://0001-arm64-defconfig-drop-unused-BACKLIGHT_GENERIC-option.patch \
    file://no-power-avs.patch \
    file://enable-realtek-R8169.cfg \
    file://enable-usb_conn_gpio.cfg \
    "
# Since we use the intree defconfig and the preempt-rt turns off some configs
# do_kernel_configcheck will display warnings. So, lets disable it.
KCONF_AUDIT_LEVEL:n1sdp:pn-linux-yocto-rt = "0"

#
# SGI575 KMACHINE
#
COMPATIBLE_MACHINE:sgi575 = "sgi575"
KBUILD_DEFCONFIG:sgi575 = "defconfig"
KCONFIG_MODE:sgi575 = "--alldefconfig"

#
# Total Compute (TC0/TC1) KMACHINE
#
COMPATIBLE_MACHINE:tc = "(tc0|tc1)"
KCONFIG_MODE:tc = "--alldefconfig"
FILESEXTRAPATHS:prepend:tc := "${ARMBSPFILESPATHS}:${THISDIR}/linux-arm64-ack-5.10/tc:"
SRC_URI:append:tc = " \
    file://gki_defconfig \
    file://0001-drm-Add-component-aware-simple-encoder.patch \
    file://0002-drm-arm-komeda-add-RENDER-capability-to-the-device-n.patch \
    file://0003-dt-bindings-mailbox-arm-mhuv2-Add-bindings.patch \
    file://0004-mailbox-arm_mhuv2-Add-driver.patch \
    file://0005-mailbox-arm_mhuv2-Fix-sparse-warnings.patch \
    file://0006-mailbox-arm_mhuv2-make-remove-callback-return-void.patch \
    file://0007-mailbox-arm_mhuv2-Skip-calling-kfree-with-invalid-po.patch \
    file://0008-arm64-smccc-Add-support-for-SMCCCv1.2-extended-input.patch \
    file://0009-firmware-arm_ffa-Add-initial-FFA-bus-support-for-dev.patch \
    file://0010-firmware-arm_ffa-Add-initial-Arm-FFA-driver-support.patch \
    file://0011-firmware-arm_ffa-Add-support-for-SMCCC-as-transport-.patch \
    file://0012-firmware-arm_ffa-Setup-in-kernel-users-of-FFA-partit.patch \
    file://0013-firmware-arm_ffa-Add-support-for-MEM_-interfaces.patch \
    file://0014-tee-add-sec_world_id-to-struct-tee_shm.patch \
    file://0015-optee-simplify-optee_release.patch \
    file://0016-optee-sync-OP-TEE-headers.patch \
    file://0017-optee-refactor-driver-with-internal-callbacks.patch \
    file://0018-optee-add-a-FF-A-memory-pool.patch \
    file://0019-optee-add-FF-A-support.patch \
    file://0021-arm_ffa-add-support-for-FFA-v1.1.patch \
    file://0022-coresight-etm4x-Save-restore-TRFCR_EL1.patch \
    file://0023-coresight-etm4x-Use-Trace-Filtering-controls-dynamic.patch \
    "
KERNEL_FEATURES:append:tc = " bsp/arm-platforms/tc.scc"
KERNEL_FEATURES:append:tc1 = " bsp/arm-platforms/tc-autofdo.scc"
