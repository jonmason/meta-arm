SRCREV ?= "41e8d7be674f98a0f3bef67b16ea2162109fd522"
SRCREV_meta ?= "e32057eca987b7abbe3eb47ba36f06af8711278a"

# KBRANCH is set to n1sdp by default as there is no master or 5.4 branch on the repository
KBRANCH ?= "n1sdp"
KMETA_BRANCH ?= "yocto-5.4"

SRC_URI_append = " file://fix-bfd-link.patch"

require linux-linaro-arm.inc
