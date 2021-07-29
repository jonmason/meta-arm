# Machine specific u-boot

THIS_DIR := "${THISDIR}"
FILESEXTRAPATHS_prepend = "${THIS_DIR}/${BP}:"

#
# TC0 MACHINE
#
SRC_URI_append_tc0 = " \
    file://0001-board-armltd-Remove-bootargs-from-Total-Compute-conf.patch \
    file://0002-cmd-part-Correct-error-handling.patch \
    file://bootargs.cfg \
    "
