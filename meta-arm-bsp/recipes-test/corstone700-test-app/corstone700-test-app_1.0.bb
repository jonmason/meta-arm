SUMMARY = "CORSTONE700 systems communications tests"
DESCRIPTION = "This is a Linux userspace tool to test the communication between Corstone700 cores"
HOMEPAGE = "https://git.linaro.org/landing-teams/working/arm/test-apps.git"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://license.md;md5=e44b2531cd6ffe9dece394dbe988d9a0"

SRC_URI = "git://git.linaro.org/landing-teams/working/arm/test-apps.git;protocol=https"
SRCREV = "ecd93a275d11cf08f670a97783110bd698250963"
PV .= "~git${SRCPV}"

COMPATIBLE_MACHINE = "(corstone700)"

S = "${WORKDIR}/git"

do_compile() {
    ${CC} ${S}/test-app.c ${CFLAGS} ${LDFLAGS} -o ${S}/test-app
}

do_install() {
    install -D -p -m 0755 ${S}/test-app ${D}${bindir}/test-app
}
