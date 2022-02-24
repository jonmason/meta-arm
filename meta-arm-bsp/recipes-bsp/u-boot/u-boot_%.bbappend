# Machine specific u-boot

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

#
# Corstone1000 64-bit machines
#
CORSTONE1000_DEVICE_TREE:corstone1000-mps3 = "corstone1000-mps3"
CORSTONE1000_DEVICE_TREE:corstone1000-fvp = "corstone1000-fvp"
EXTRA_OEMAKE:append:corstone1000 = ' DEVICE_TREE=${CORSTONE1000_DEVICE_TREE}'

SYSROOT_DIRS:append:corstone1000 = " /boot"

SRC_URI:append:corstone1000 = " \
      file://0001-arm-add-corstone1000-platform.patch \
      file://0002-arm-corstone1000-enable-devicetree-in-defconfig.patch \
      file://0003-usb-common-move-urb-code-to-common.patch \
      file://0004-usb-add-isp1760-family-driver.patch \
      file://0005-corstone1000-enable-isp1763-and-usb-stack.patch \
      file://0006-corstone1000-enable-support-for-FVP.patch \
      file://0007-arm-corstone1000-sharing-PSCI-DTS-node-between-FVP-a.patch \
      file://0008-arm-corstone1000-Emulated-RTC-Support.patch \
      file://0009-arm-corstone1000-execute-uboot-from-DDR.patch \
      file://0010-cmd-load-add-load-command-for-memory-mapped.patch \
      file://0011-arm-corstone1000-enable-boot-using-uefi.patch \
      file://0012-arm-corstone1000-enable-uefi-secure-boot.patch \
      file://0013-arm-corstone1000-enable-handlers-for-uefi-variables.patch \
      file://0014-arm-corstone1000-enable-efi-capsule-options.patch \
      file://0015-arm-dts-add-initial-devicetree-corstone1000-mps3.patch \
      file://0016-arm-corstone1000-adding-PSCI-device-tree-node.patch \
      file://0017-arm-corstone1000-amend-kernel-bootargs-with-ip-dhcp-.patch \
      file://0018-arm_ffa-introducing-Arm-FF-A-low-level-driver.patch \
      file://0019-arm_ffa-introducing-armffa-command.patch \
      file://0020-arm_ffa-introducing-test-module-for-UCLASS_FFA.patch \
      file://0021-arm_ffa-introducing-MM-communication-with-FF-A.patch \
      file://0022-arm_ffa-corstone1000-enable-FF-A-and-MM-support.patch \
      file://0023-efi-corstone1000-introduce-EFI-capsule-update.patch \
      file://0024-corstone1000-adjust-the-environment-and-heap-sizes.patch \
      file://0025-corstone1000-Update-FFA-shared-buffer-address.patch \
      file://0026-corstone1000-Disable-set-get-of-NV-variables.patch \
      file://0027-corstone1000-Make-sure-shared-buffer-contents-are-no.patch \
      file://0028-arm-corstone1000-fix-unrecognized-filesystem-type-error.patch \
      file://0029-corstone1000-set-CONFIG_PSCI_RESET.patch \
      file://0030-arm-bsp-u-boot-corstone1000-Implement-autoboot-script.patch \
      file://0031-corstone1000-change-base-address-of-kernel-in-the-fl.patch \
      file://0032-arm-corstone1000-identify-which-bank-to-load-kernel.patch \
      file://0033-corstone1000-dts-setting-the-boot-console-output.patch \
      file://0034-corstone1000-dts-remove-the-use-of-fdt_addr_r.patch \
      file://0035-efi_capsule-corstone1000-pass-interface-and-buffer-event-ids-in-w4.patch \
      file://0036-efi_boottime-corstone1000-pass-interface-and-kernel-event-ids-in-w4.patch \
      file://0037-efi_loader-remove-guid-check-from-corstone1000-confi.patch \
      file://0038-arm_ffa-removing-the-cast-when-using-binary-OR-on-FIELD_PREP.patch \
      file://0039-efi_loader-add-the-header-file-for-invalidate_dcache_all.patch \
      file://0040-Return-proper-error-code-when-rx-buffer-is-larger.patch \
      file://0041-Use-correct-buffer-size.patch \
      file://0042-Update-comm_buf-when-EFI_BUFFER_TOO_SMALL.patch \
      file://0043-Disable-DHCP-PING-config-parameters.patch \
      file://0044-Revert-corstone1000-Disable-set-get-of-NV-variables.patch \
      file://0045-corstone1000-defconfig-enable-CAPSULE_FIRMWARE_RAW-c.patch \
      file://0046-efi_loader-populate-ESRT-table-if-EFI_ESRT-config-op.patch \
      file://0047-efi_firmware-add-get_image_info-for-corstone1000.patch \
      file://0048-corstone1000-enable-ethernet-device.patch \
      file://0049-efi_loader-Fix-loaded-image-alignment.patch \
      file://0050-Comment-mm_communicate-failure-log.patch \
      file://0051-efi_loader-send-bootcomplete-message-to-secure-encla.patch \
      file://0052-efi_loader-fix-null-pointer-exception-with-get_image.patch \
      "

#
# FVP BASE
#
SRC_URI:append:fvp-base = " file://bootargs.cfg"

#
# FVP BASE ARM32
#
SRC_URI:append:fvp-base-arm32 = " file://0001-Add-vexpress_aemv8a_aarch32-variant.patch"

#
# FVP BASER
#
SRC_URI:append:fvp-baser-aemv8r64 = " \
    file://0001-armv8-Disable-pointer-authentication-traps-for-EL1.patch \
    file://0002-doc-Add-documentation-for-the-Arm-VExpress64-board-c.patch \
    file://0003-vexpress64-Refactor-header-file-to-make-it-easier-to.patch \
    file://0004-vexpress64-Clean-up-BASE_FVP-boot-configuration.patch \
    file://0005-vexpress64-Enable-OF_CONTROL-and-OF_BOARD-for-VExpre.patch \
    file://0006-vexpress64-Enable-VIRTIO_NET-network-driver.patch \
    file://0007-armv8-Add-ARMv8-MPU-configuration-logic.patch \
    file://0008-armv8-Allow-disabling-exception-vectors-on-non-SPL-b.patch \
    file://0009-armv8-ARMV8_SWITCH_TO_EL1-improvements.patch \
    file://0010-armv8-Make-disabling-HVC-configurable-when-switching.patch \
    file://0011-vexpress64-Do-not-set-COUNTER_FREQUENCY.patch \
    file://0012-vexpress64-Add-BASER_FVP-vexpress-board-variant.patch \
    "
