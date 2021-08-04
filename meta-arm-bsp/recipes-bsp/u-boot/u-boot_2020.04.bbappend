#
# Corstone700 KMACHINE
#
FILESEXTRAPATHS:prepend:corstone700 := "${THISDIR}/${BP}/corstone700:"
SRC_URI:append:corstone700 = " file://0001-arm-Add-corstone700-platform.patch \
                               file://0002-boot-add-bootx-command-to-start-XiP-images.patch \
                               file://0003-boot-starting-the-XIP-kernel-using-bootx-command.patch \
                               file://0004-arm-enabling-the-arch_timer-driver.patch"
