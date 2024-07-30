require recipes-security/optee/optee-os.inc

DEPENDS += "dtc-native"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRCREV = "12d7c4ee4642d2d761e39fbcf21a06fb77141dea"
SRC_URI += " \
    file://0003-optee-enable-clang-support.patch \
    file://0001-checkconf.mk-do-not-use-full-path-to-generate-guard-.patch \
    file://0001-mk-compile.mk-remove-absolute-build-time-paths.patch \
"
