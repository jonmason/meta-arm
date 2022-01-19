# TC specific configuration

COMPATIBLE_MACHINE = "(tc?)"
HAFNIUM_PLATFORM = "secure_tc"

FILESEXTRAPATHS:prepend:tc := "${THISDIR}/files/tc:"
SRC_URI:append = " \
		file://0001-fix-fail-mapping-if-start-address-exceeds-page-table.patch \
		file://0002-Extend-Stage-1-mapping-limit.patch \
		 "
