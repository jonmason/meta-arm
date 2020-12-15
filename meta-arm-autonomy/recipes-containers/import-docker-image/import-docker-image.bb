#
# This recipe imports a docker container image to the xenguest image
# Notes:
# - Users should add docker in the local.conf of their target with
# DISTRO_FEATURES += " docker" to make sure docker is installed.
# - The CONTAINER_IMAGE_FILE variable defines the docker
# container image to be imported and should be set in local.conf.
# - The CONTAINER_IMAGE_FILE_KEEP variable defines the
# behaviour that if the container image file is kept after import.
# Setting this variable to 1 means keep the container image file after
# import. This variable can be set in local.conf.
# - The CONTAINER_IMAGE_NAME_AND_TAG variable defines the name and
# tag of the imported image. The value of this variable should follow
# the format of `NAME:TAG`. This variable can be set in local.conf.
#

DESCRIPTION = "Import a docker image to xenguest"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

CONTAINER_IMAGE_FILE ??= ""
CONTAINER_IMAGE_FILE_KEEP ??= ""
CONTAINER_IMAGE_NAME_AND_TAG ??= "local:local"

inherit features_check
REQUIRED_DISTRO_FEATURES = "docker"

python __anonymous() {
    # Check if `CONTAINER_IMAGE_FILE` is empty.
    container_image_file = d.getVar('CONTAINER_IMAGE_FILE')
    if not container_image_file:
        raise bb.parse.SkipRecipe("CONTAINER_IMAGE_FILE is empty")

    # In case we have a symlink we need to convert the link to its realpath.
    if os.path.islink(container_image_file):
        container_image_file = os.path.realpath(container_image_file)
        bb.warn("Given CONTAINER_IMAGE_FILE: %s is a symlink, "
                "convert the link to its realpath: %s" %
                (d.getVar('CONTAINER_IMAGE_FILE'), container_image_file))
        d.setVar('CONTAINER_IMAGE_FILE', container_image_file)

    # Check if the container image file exists.
    # The container image file here is either the real file or the symlink target.
    if not os.path.exists(container_image_file):
        raise bb.parse.SkipRecipe("CONTAINER_IMAGE_FILE: %s does not exist." %
                                  container_image_file)

    # Here we can ensure that the CONTAINER_IMAGE_FILE exists and is valid.
    # Therefore we can append this file to SRC_URI.
    d.appendVar('SRC_URI',  ' file://' + container_image_file + ';unpack=0')
}

S = "${WORKDIR}"
SRC_URI = "file://import_container.sh"

inherit update-rc.d
INITSCRIPT_PARAMS = "start 30 2 3 4 5 ."
INITSCRIPT_NAME = "import_container.sh"

do_install() {
    install -d ${D}${sysconfdir}/init.d
    install -d -m 755 ${D}${datadir}/docker/images

    install -m 777 ${CONTAINER_IMAGE_FILE} ${D}${datadir}/docker/images/.
    install -m 755 import_container.sh ${D}${sysconfdir}/init.d

    BASENAME_CONTAINER_IMAGE_FILE=$(basename "${CONTAINER_IMAGE_FILE}")

    sed -i "s,###CONTAINER_IMAGE_FILE###,${BASENAME_CONTAINER_IMAGE_FILE}," \
           ${D}${sysconfdir}/init.d/import_container.sh
    sed -i "s,###CONTAINER_IMAGE_NAME_AND_TAG###,${CONTAINER_IMAGE_NAME_AND_TAG}," \
           ${D}${sysconfdir}/init.d/import_container.sh
    sed -i "s,###CONTAINER_IMAGE_FILE_KEEP###,${CONTAINER_IMAGE_FILE_KEEP}," \
           ${D}${sysconfdir}/init.d/import_container.sh
}

FILES_${PN} += "${datadir}/docker/images"
RDEPENDS_${PN} = "packagegroup-docker-runtime-minimal"
