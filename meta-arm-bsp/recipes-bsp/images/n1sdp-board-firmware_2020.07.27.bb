SUMMARY = "Board Firmware binaries for N1SDP"
SECTION = "firmware"

LICENSE = "STM-SLA0044-Rev5"
LIC_FILES_CHKSUM = "file://LICENSES/STM.TXT;md5=4b8dab81d0bfc0a5f63c9a983402705b"

inherit deploy

INHIBIT_DEFAULT_DEPS = "1"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "n1sdp"

SRC_URI = "https://git.linaro.org/landing-teams/working/arm/n1sdp-board-firmware.git/snapshot/${BPN}-N1SDP-${PV}.tar.gz"
SRC_URI[sha256sum] = "57feba404026f2d6d49c167d63e0e84653ad8b808b13e2244b81fea9e0d58d66"

S = "${WORKDIR}/${BPN}-N1SDP-${PV}"

INSTALL_DIR = "/n1sdp-board-firmware_source"

do_install() {
    rm -rf ${S}/SOFTWARE
    install -d ${D}${INSTALL_DIR}
    cp -Rp --no-preserve=ownership ${S}/* ${D}${INSTALL_DIR}
}

FILES:${PN} = "${INSTALL_DIR}"
SYSROOT_DIRS += "${INSTALL_DIR}"

do_deploy() {
    install -d ${DEPLOYDIR}${INSTALL_DIR}
    cp -Rp --no-preserve=ownership ${S}/* ${DEPLOYDIR}${INSTALL_DIR}
}
addtask deploy after do_install before do_build
