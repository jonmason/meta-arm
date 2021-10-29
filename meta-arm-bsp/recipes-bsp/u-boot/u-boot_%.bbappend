# Machine specific u-boot

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

#
# Corstone1000 64-bit machines
#

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
      "

#
# FVP BASE
#
SRC_URI:append:fvp-base = " file://bootargs.cfg"

#
# FVP BASE ARM32
#
SRC_URI:append:fvp-base-arm32 = " file://0001-Add-vexpress_aemv8a_aarch32-variant.patch"
