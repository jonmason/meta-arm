# Machine specific u-boot

THIS_DIR := "${THISDIR}"
FILESEXTRAPATHS:prepend = "${THIS_DIR}/${BP}/tc:"

#
# TC0 MACHINE
#
SRC_URI:append:tc0 = " \
    file://0001-board-armltd-Remove-bootargs-from-Total-Compute-conf.patch \
    file://0002-cmd-part-Correct-error-handling.patch \
    file://bootargs.cfg \
    "
#
# TC1 MACHINE
#
SRC_URI:append:tc1 = " \
    file://0001-board-armltd-Remove-bootargs-from-Total-Compute-conf.patch \
    file://0002-cmd-part-Correct-error-handling.patch \
    file://bootargs.cfg \
    "
