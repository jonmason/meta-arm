# Firmware Image Package (FIP)
# It is a packaging format used by TF-A to package the
# firmware images in a single binary.

DESCRIPTION = "fiptool - Trusted Firmware tool for packaging"
LICENSE = "BSD-3-Clause"

SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;destsuffix=fiptool-${PV};protocol=https;branch=master \
           file://ssl.patch"
LIC_FILES_CHKSUM = "file://docs/license.rst;md5=713afe122abbe07f067f939ca3c480c5"

# Use fiptool from TF-A v2.5
SRCREV = "c158878249f1bd930906ebd744b90d3f2a8265f1"

DEPENDS += "openssl-native"

inherit native

EXTRA_OEMAKE = "V=1 HOSTCC='${BUILD_CC}' OPENSSL_DIR=${STAGING_DIR_NATIVE}/${prefix_native}"

do_compile () {
    # This is still needed to have the native fiptool executing properly by
    # setting the RPATH
    sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
    sed -i '/^INCLUDE_PATHS/ s,$, \$\{BUILD_CFLAGS},' ${S}/tools/fiptool/Makefile

    oe_runmake fiptool
}

do_install () {
    install -D -p -m 0755 tools/fiptool/fiptool ${D}${bindir}/fiptool
}
