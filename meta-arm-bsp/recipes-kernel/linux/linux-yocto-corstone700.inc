FILESEXTRAPATHS:prepend := "${THISDIR}:${THISDIR}/files:"

COMPATIBLE_MACHINE = "${MACHINE}"

KMACHINE = "corstone700"

SRC_URI += " \
           file://0001-arm-support-for-a-single-ARMv7-A-based-platform.patch       \
           file://0002-arm-Add-tiny-vexpress-machine.patch                         \
           file://0003-arm-introduce-corstone700_defconfig.patch                   \
           file://0004-add-driver-of-mailbox-handling-unit-controller-versi.patch  \
           file://0005-add-rpmsg-based-on-rpmsg-char-driver-using-mailbox.patch    \
           file://0006-enable-arm-MHU-driver-and-RPMSG-char-driver.patch           \
           file://0007-allow-creation-of-multiple-arm-rpmsg-channels.patch         \
           file://0008-mailbox-enable-combined-receiver-interrupt-when-usin.patch  \
           file://0009-misc-arm-add-corstone700-external-system-harness-dri.patch  \
           file://0010-arm-containerize-endpoint-and-mailbox-information.patch     \
           file://0011-arm-couple-mailbox-channel-ownership-to-rpmsg-endpoi.patch  \
           file://0012-mailbox-arm_mhu_v2-add-new-AMBA-ID-to-support-MHU-v2.patch  \
           file://0013-mailbox-arm_mhu_v2-dynamic-allocation-of-channels.patch     \
           file://0014-defconfig-adjust-XIP-physical-address-to-3MB-offset.patch   \
           file://0015-arm-Kconfig-disable-ARM_VIRT-extension-if-XIP_KERNEL.patch  \
           file://0016-corstone700_defconfig-use-DDR-address-instead-of-sha.patch  \
           file://0017-corstone700_defconfig-enable-configs-for-cramfs-xip.patch   \
           file://0018-usb-isp1760-move-to-regmap-for-register-access.patch        \
           file://0019-usb-isp1760-hcd-refactor-mempool-config-and-setup.patch     \
           file://0020-usb-isp1760-add-support-for-isp1763.patch                   \
           "

KERNEL_IMAGETYPE = "xipImage"

KCONFIG_MODE = "--alldefconfig"

SRC_URI:append = " ${SRC_URI_KMETA}"

KERNEL_EXTRA_FEATURES = "bsp/arm-platforms/corstone700-bsp.scc"
KERNEL_FEATURES:append = " ${KERNEL_EXTRA_FEATURES}"

KERNEL_FEATURES:append:corstone700-fvp = " \
    ${@bb.utils.contains('MACHINE_FEATURES', \
                         'eth_lan91c111', \
                         'bsp/arm-platforms/corstone700/xip_dhcp_cmdline.cfg \
                          bsp/arm-platforms/corstone700/eth_lan91c111.scc', \
                         'bsp/arm-platforms/corstone700/xip_cmdline.cfg', \
                          d)}"

KERNEL_FEATURES:append:corstone700-mps3 = " \
    ${@bb.utils.contains('MACHINE_FEATURES', \
                         'eth_lan9115', \
                         'bsp/arm-platforms/corstone700/xip_dhcp_cmdline.cfg \
                          bsp/arm-platforms/corstone700/eth_lan9115.scc', \
                         'bsp/arm-platforms/corstone700/xip_cmdline.cfg', \
                          d)} \
    ${@bb.utils.contains('MACHINE_FEATURES', \
                         'usb_host', \
                         'bsp/arm-platforms/corstone700/usb_host.cfg', \
                        '', \
                          d)}"
