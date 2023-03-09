require optee-os.inc

DEPENDS += "dtc-native"

FILESEXTRAPATHS:prepend := "${THISDIR}/optee-os-3.19.0:"

SRCREV = "afacf356f9593a7f83cae9f96026824ec242ff52"
SRC_URI:append = " \
    file://0001-core-Define-section-attributes-for-clang.patch \
   "
