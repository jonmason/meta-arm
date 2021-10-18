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
# TC0 and TC1 MACHINES
#
SRC_URI:append:tc = " file://bootargs.cfg"
