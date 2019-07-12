SUMMARY = "Cramfs tools"
DESCRIPTION = "Cramfs tools to create cramfs images with support to XIP"
HOMEPAGE = "https://github.com/npitre/cramfs-tools"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=393a5ca445f6965873eca0259a17f833"

SRC_URI = "git://github.com/npitre/cramfs-tools;protocol=https;nobranch=1"

SRCREV = "23d032e6e0a973810c6aedf165441592641b60f4"

BBCLASSEXTEND = "native"

S = "${WORKDIR}/git"

do_compile () {
      oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install ${S}/mkcramfs ${D}${bindir}
    install ${S}/cramfsck ${D}${bindir}
}
