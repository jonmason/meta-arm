SUMMARY = "CORSTONE700 Host Test App"
DESCRIPTION = "CORSTONE700 Host Test App"
DEPENDS += " coreutils-native "
LICENSE="BSD"
LIC_FILES_CHKSUM = "file://license.md;md5=e44b2531cd6ffe9dece394dbe988d9a0"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI = "git://${USER}@git.linaro.org/landing-teams/working/arm/test-apps.git;protocol=https;branch=master"
SRCREV = "CORSTONE-700-2019.09.23"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

COMPATIBLE_MACHINE = "(corstone700)"

PLATFORM = "corstone700"

LDFLAGS[unexport] = "1"

do_compile() {
	mkdir -p ${B}
	${CC} ${S}/test-app.c -o ${S}/test-app --static
	cp ${S}/test-app ${B}/test-app
}

do_install() {
	install -d ${D}/${bindir}/
	install -m 0755 ${B}/test-app ${D}${bindir}/test-app
}

FILES_${PN} += "${bindir}/test-app"
