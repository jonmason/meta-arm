#
# TC0 MACHINE specific configurations
#

FILESEXTRAPATHS_prepend := "${THISDIR}/linux-arm64-ack-4.19:${THISDIR}/files:"

SRC_URI_append = " \
    file://defconfig \
    file://0001-drm-Add-component-aware-simple-encoder.patch \
    file://0002-swap-red-and-blue-colors-in-HDLCD-driver.patch \
    file://0001-scripts-dtc-Remove-redundant-YYLOC-global-declaratio.patch \
    "

KCONFIG_MODE = "--alldefconfig"

COMPATIBLE_MACHINE = "tc0"
