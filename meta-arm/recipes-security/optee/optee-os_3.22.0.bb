require optee-os.inc

DEPENDS += "dtc-native"

FILESEXTRAPATHS:prepend := "${THISDIR}/optee-os-3.22.0:"

SRCREV = "001ace6655dd6bb9cbe31aa31b4ba69746e1a1d9"
SRC_URI += " \
    file://0001-core-Define-section-attributes-for-clang.patch \
   "
