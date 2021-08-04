#
# This recipe adds an init script to import the containers added by
# docker_extern_containers.bbclass at boot time
# Notes:
# docker_extern_containers.bbclass creates a manifest file which contains
# the columns:   archive   name   tag   keep
# for each container. This file is read by the import_containers
# script to determine the parameters of the import
#
# Since the script needs knowledge of the values of $CONTAINERS_INSTALL_DIR
# and $CONTAINERS_MANIFEST these are substituted for placeholder strings when
# the script is installed.

DESCRIPTION = "Add init script to import docker images at boot"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit docker_extern_containers

SRC_URI = "file://import_containers.sh"

inherit update-rc.d
INITSCRIPT_PARAMS = "start 30 2 3 4 5 ."
INITSCRIPT_NAME = "import_containers.sh"

S = "${WORKDIR}"
do_install:append() {
    install -d ${D}${sysconfdir}/init.d
    install -m 755 import_containers.sh ${D}${sysconfdir}/init.d

    sed -i "s,###CONTAINERS_INSTALL_DIR###,${CONTAINERS_INSTALL_DIR}," \
           ${D}${sysconfdir}/init.d/import_containers.sh
    sed -i "s,###CONTAINERS_MANIFEST###,${CONTAINERS_MANIFEST}," \
           ${D}${sysconfdir}/init.d/import_containers.sh
}
