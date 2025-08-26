require recipes-security/optee/optee-os.inc

DEPENDS += "dtc-native"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

# v4.7.0
SRCREV = "86846f4fdf14f25b50fd64a87888ca9fe85a9e2b"
