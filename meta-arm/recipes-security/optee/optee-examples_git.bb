require recipes-security/optee/optee-examples.inc

# v4.7.0
SRCREV = "14321a0607db16099d158478b21a2b2e37b3a935"
PV .= "+git"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
