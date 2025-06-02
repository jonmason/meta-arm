require recipes-security/optee/optee-client.inc

# v4.6.0
SRCREV = "02e7f9213b0d7db9c35ebf1e41e733fc9c5a3f75"
PV .= "+git"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI += "file://0001-tee-supplicant-update-udev-systemd-install-code.patch"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
