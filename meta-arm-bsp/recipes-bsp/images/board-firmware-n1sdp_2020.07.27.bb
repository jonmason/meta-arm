DESCRIPTION = "Board Firmware binaries for N1SDP"

# Board-firmware-n1sdp custom license is whitelisted in n1sdp.conf file.
# Uncomment, or copy this line to your local.conf to build board firmware,
# if you are using custom n1sdp.conf file.
# Please make sure to check the applicable license beforehand!
#LICENSE_FLAGS_WHITELIST = "stm-sla0044"

LICENSE = "STM-SLA0044-Rev5"
LICENSE_FLAGS = "stm-sla0044"

LIC_FILES_CHKSUM = "file://${S}/LICENSES/STM.TXT;md5=4b8dab81d0bfc0a5f63c9a983402705b"

SECTION = "firmware"

inherit deploy

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "n1sdp"
RM_WORK_EXCLUDE += "${PN}"

PV = "2020.07.27"
TAG = "N1SDP-${PV}"
FIRMWARE_TARBALL = "n1sdp-board-firmware-${TAG}"
UNPACK_DIR = "n1sdp-board-firmware_source"
S = "${WORKDIR}/${UNPACK_DIR}"

SRC_URI = "https://git.linaro.org/landing-teams/working/arm/n1sdp-board-firmware.git/snapshot/${FIRMWARE_TARBALL}.tar.gz;unpack=0"
SRC_URI[md5sum] = "8ba3807ff8f222201154861f11524b14"
SRC_URI[sha256sum] = "57feba404026f2d6d49c167d63e0e84653ad8b808b13e2244b81fea9e0d58d66"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    cd ${WORKDIR}
    tar -xvaf ${WORKDIR}/${FIRMWARE_TARBALL}.tar.gz --exclude=${FIRMWARE_TARBALL}/SOFTWARE/*
    mv -v ${WORKDIR}/${FIRMWARE_TARBALL}/* ${S}

    cp -R --no-dereference --preserve=mode,links -v ${S} ${D}
}
do_install[dirs] += "${S}"
do_install[cleandirs] += "${S}"

FILES_${PN} = "/${UNPACK_DIR}/*"
SYSROOT_DIRS += "/${UNPACK_DIR}"
addtask install after do_unpack before do_populate_lic

do_deploy() {
    cp -av ${S} ${DEPLOYDIR}
}
addtask deploy after do_install
