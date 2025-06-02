require recipes-security/optee/optee-os.inc

DEPENDS += "dtc-native"

# v4.6.0
SRCREV = "71785645fa6ce42db40dbf5a54e0eaedc4f61591"
SRC_URI += " \
    file://0001-optee-enable-clang-support.patch \
    file://0002-Add-optee-ta-instanceKeepCrashed.patch \
   "
PV .= "+git"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
