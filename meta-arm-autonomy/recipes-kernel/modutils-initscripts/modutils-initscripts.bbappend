FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " file://fix-modules-dep-creation.patch"

# We want to have modutils.sh running after checkroot.sh (05)
INITSCRIPT_PARAMS = "start 06 S ."
