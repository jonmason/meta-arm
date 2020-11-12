FILESEXTRAPATHS_prepend := "${THISDIR}/linux-yocto-5.6:"

SRC_URI_append = " file://0001-libtraceevent-Fix-build-with-binutils-2.35.patch \
                   file://0002-perf-cs-etm-Move-definition-of-traceid_list-global-v.patch"

#
# Corstone700 KMACHINE
#
MACHINE_KERNEL_REQUIRE ?= ""
MACHINE_KERNEL_REQUIRE_corstone700 = "linux-yocto-corstone700.inc"

require ${MACHINE_KERNEL_REQUIRE}
