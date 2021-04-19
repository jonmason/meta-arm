FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append_qemuarm64-secureboot = " file://zone_dma_revert.patch"
