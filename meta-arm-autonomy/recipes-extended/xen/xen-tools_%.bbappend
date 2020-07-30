FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-vif-nat-fix-hostname.patch \
            file://0002-vif-nat-fix-symlink-removal.patch \
           "
