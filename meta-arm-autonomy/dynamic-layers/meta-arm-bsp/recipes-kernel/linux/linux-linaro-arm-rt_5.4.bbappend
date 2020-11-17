FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-5.4:"

SRC_URI_append = " \
    file://0001-xen-use-handle_fasteoi_irq-to-handle-xen-dynamic-eve.patch \
    "
