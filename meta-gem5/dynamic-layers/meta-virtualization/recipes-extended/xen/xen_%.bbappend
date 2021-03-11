# gem5-arm64 support
COMPATIBLE_MACHINE_gem5-arm64 = "gem5-arm64"
FILESEXTRAPATHS_prepend_gem5-arm64 := "${THISDIR}/files:"
SRC_URI_append_gem5-arm64 = " file://early-printk.cfg"
