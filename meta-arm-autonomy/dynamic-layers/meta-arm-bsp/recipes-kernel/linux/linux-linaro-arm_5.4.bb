SRCREV ?= "84baaae9e751c058717d9702438429257f077f03"
SRCREV_meta ?= "e32057eca987b7abbe3eb47ba36f06af8711278a"

# KBRANCH is set to n1sdp by default as there is no master or 5.4 branch on the repository
KBRANCH ?= "n1sdp"
KMETA_BRANCH ?= "yocto-5.4"

# Apply following patches
SRC_URI_append = " \
    file://fix-bfd-link.patch \
    file://perf-fixup-gcc10-01.patch \
    file://perf-fixup-gcc10-02.patch \
    file://perf-fixup-gcc10-03.patch \
    file://perf-fixup-gcc10-04.patch \
    "

require linux-linaro-arm.inc
