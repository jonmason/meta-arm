# Xenguest manager recipe
#
# xenguest-manager is a tool to control xen guests (e.g. create, start, stop)
#
# Usage documentation for the xenguest-manager tool can be found in
# meta-arm-autonomy/documentation/xenguest-manager.md including the
# customizable bitbake variables.

DESCRIPTION = "Xen Guest Manager"
LICENSE = "MIT"

SRC_URI = " \
    file://xenguest-manager \
    file://xenguest-init \
    file://logrotate-xenguest \
    "
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

S = "${WORKDIR}"

XENGUEST_MANAGER_VOLUME_DEVICE ?= "/dev/sda2"
XENGUEST_MANAGER_VOLUME_NAME ?= "vg-xen-$(basename ${XENGUEST_MANAGER_VOLUME_DEVICE})"
XENGUEST_MANAGER_LOG_LEVEL ?= "ERROR"
#XENGUEST_MANAGER_GUEST_DIR set in xenguest.conf

require conf/xenguest.conf

# We add an init script to create and start guests automatically
# run start script after xen-tools and run stop script before xen-tools
INITSCRIPT_NAME = "xenguest"
INITSCRIPT_PARAMS = "start 90 2 3 4 5 . stop 79 0 1 6 ."

inherit allarch update-rc.d

do_compile() {
    echo "XENGUEST_VOLUME_DEVICE=\"${XENGUEST_MANAGER_VOLUME_DEVICE}\"" > \
        xenguest-manager.conf
    echo "XENGUEST_VOLUME_NAME=\"${XENGUEST_MANAGER_VOLUME_NAME}\"" >> \
        xenguest-manager.conf
    echo "XENGUEST_GUEST_DIR=\"${XENGUEST_MANAGER_GUEST_DIR}\"" >> \
        xenguest-manager.conf
    echo "XENGUEST_LOG_LEVEL=\"${XENGUEST_MANAGER_LOG_LEVEL}\"" >> \
        xenguest-manager.conf
}

do_install() {
    install -d -m 755 ${D}${bindir}
    install -m 755 xenguest-manager ${D}${bindir}/.
    install -d -m 755 ${D}${sysconfdir}/xenguest
    install -m 644 xenguest-manager.conf ${D}${sysconfdir}/xenguest/.
    install -d -m 755 ${D}${sysconfdir}/init.d
    install -m 755 xenguest-init ${D}${sysconfdir}/init.d/${INITSCRIPT_NAME}
    install -d -m 755 ${D}${XENGUEST_GUEST_DIR}
    install -d -m 755 ${D}${sysconfdir}/logrotate.d
    install -m 644 logrotate-xenguest ${D}${sysconfdir}/logrotate.d/xenguest
}

# Things that we need on the target
RDEPENDS:${PN} += "bash xenguest-mkimage lvm2 xen-tools parted e2fsprogs \
                   dosfstools logrotate"

FILES:${PN} += "${bindir}/xenguest-manager \
               ${sysconfdir}/xenguest"
