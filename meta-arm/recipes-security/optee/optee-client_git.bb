require recipes-security/optee/optee-client.inc

# v4.7.0
SRCREV = "23c112a6f05cc5e39bd4aaf52ad515cad532237d"
PV .= "+git"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI += "file://0001-tee-supplicant-update-udev-systemd-install-code.patch"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
