require recipes-bsp/scp-firmware/scp-firmware_2.15.0.bb

SRCBRANCH = "main"
SRCREV  = "b34e5ceb5bab4bb351e0ba4b86c2f8a539cdbbb4"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"
