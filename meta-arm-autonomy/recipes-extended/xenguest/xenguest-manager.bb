# Xenguest manager recipe
#
# xenguest-manager is a tool to control xen guest (e.g. create, start, stop)
#

DESCRIPTION = "Xen Guest Manager"
LICENSE = "MIT"

SRC_URI = " \
    file://xenguest-manager \
    file://xenguest-init \
    "
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

S = "${WORKDIR}"

# Please refer to documentation/xenguest-manager.md for documentation on those
# parameters
XENGUEST_MANAGER_VOLUME_DEVICE ?= "/dev/sda2"
XENGUEST_MANAGER_VOLUME_NAME ?= "vg-xen"
XENGUEST_MANAGER_GUEST_DIR ?= "${datadir}/guests/"

# We add an init script to create and start guests automatically
INITSCRIPT_NAME = "xenguest"
INITSCRIPT_PARAMS = "defaults 90"

inherit update-rc.d

do_compile() {
    echo "XENGUEST_VOLUME_DEVICE=\"${XENGUEST_MANAGER_VOLUME_DEVICE}\"" > \
        xenguest-manager.conf
    echo "XENGUEST_VOLUME_NAME=\"${XENGUEST_MANAGER_VOLUME_NAME}\"" >> \
        xenguest-manager.conf
    echo "XENGUEST_GUEST_DIR=\"${XENGUEST_MANAGER_GUEST_DIR}\"" >> \
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
}

# Things that we need on the target
RDEPENDS_${PN} += "bash tar xenguest-mkimage lvm2 xen-tools parted e2fsprogs dosfstools"

FILES_${PN} += "${bindir}/xenguest-manager \
               ${sysconfdir}/xenguest"
