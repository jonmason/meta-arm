require recipes-security/optee/optee-os.inc

DEPENDS += "dtc-native"

# v4.7.0
SRCREV = "86846f4fdf14f25b50fd64a87888ca9fe85a9e2b"
PV .= "+git"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
