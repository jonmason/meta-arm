# Firmware Image Package (FIP)
# It is a packaging format used by TF-A to package the
# firmware images in a single binary.

DESCRIPTION = "fiptool - Trusted Firmware tool for packaging"
LICENSE = "BSD-3-Clause"

SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https"
LIC_FILES_CHKSUM = "file://license.rst;md5=e927e02bca647e14efd87e9e914b2443"

# Use fiptool from TF-A v1.5
SRCREV = "ed8112606c54d85781fc8429160883d6310ece32"

DEPENDS += "openssl-native"

inherit native

S = "${WORKDIR}/git"

do_compile () {
    # These changes are needed to have the fiptool compiling and executing properly
    sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
    sed -i '/^INCLUDE_PATHS/ s,$, \$\{BUILD_CFLAGS},' ${S}/tools/fiptool/Makefile

    oe_runmake fiptool
}

do_install () {
    install -d ${D}${bindir}/
    install -m 0755 tools/fiptool/fiptool ${D}${bindir}
}
