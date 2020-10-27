# TF-A spm

SRCREV_FORMAT = "spm"

SRCREV_spm = "764fd2eb2ece8b5bddc802cc8369743a283cd7d7"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append_tc0 = " file://0001-FF-A-Booting-SPs-according-to-boot-order.patch"

LIC_FILES_CHKSUM = "file://LICENSE;md5=782b40c14bad5294672c500501edc103"

COMPATIBLE_MACHINE = "tc0"

SPM_PLATFORM = "secure_tc0_clang"
SPM_INSTALL_TARGET = "hafnium.bin"
