require recipes-security/optee/optee-client.inc

# v4.8.0
SRCREV = "9d6f69844ff60ec0966cf3659abcc38eda8b31ea"
PV .= "+git"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI += "file://0001-tee-supplicant-update-udev-systemd-install-code.patch"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
