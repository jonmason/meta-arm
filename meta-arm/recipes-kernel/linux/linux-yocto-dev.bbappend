FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append_qemuarm64-secureboot = " file://tee.cfg"

