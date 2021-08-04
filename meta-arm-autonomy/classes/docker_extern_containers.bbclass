# Docker Extern Containers
#
# This class allows docker image tarballs to be installed in the rootfs
#
# The images can be selected using the variable CONTAINER_IMAGE_FILES which
# should contain a space seperated list of absolute paths or yocto urls for
# docker images that have been exported using docker export:
# - https://docs.docker.com/engine/reference/commandline/export/
#
# src_uri_parse_var.bbclass is used to parse CONTAINER_IMAGE_FILES
#
# There are 4 supported formats for CONTAINER_IMAGE_FILES entries:
#
# - http/https url
#   - CONTAINER_IMAGE_FILES = "https://[url]:[port]/alpine.tar;md5sum=..."
#
# - file:// absolute local path from root
#   - CONTAINER_IMAGE_FILES = "file:///containers/alpine2.tar"
#
# - file:// path relative to FILESEXTRAPATHS
#   - CONTAINER_IMAGE_FILES = "file://foo/alpine3.tar"
#     FILESEXTRAPATHS .= "/containers:"
#
# - plain absolute local path from root
#   - CONTAINER_IMAGE_FILES = "/containers/foo/bar/alpine4.tar"
#
# It is not recommended to use other yocto URL types, as they may result in
# undefined behaviour.
#
# A semicolon seperated list of install arguments can follow each image path:
# - conname : the name that will be attached when the image is imported
#             (default: [filename, without extension])
# - contag  : the tag that will be attached when the image is imported
#             (default: local)
# - conkeep : Flag for whether the exported container image file should be
#             kept once the import has been completed
#             (default: 0)
#
# Any other arguments, for example an md5sum, will be assumed to be fetch
# arguments, and will be kept when the path is added to the SRC_URI
#
# e.g.  CONTAINER_IMAGE_FILES = "\
# https://[url]:[port]/alpine.tar;md5sum=[checksum];conkeep=1 \
# file:///containers/alpine2.tar;contag=latest;conname=docker2 \
# file://foo/alpine3.tar \
# /containers/foo/bar/alpine4.tar;contag=1.0;conkeep=1 "
#
# Resulting Manifest:
# ARCHIVE     NAME    TAG    KEEP
# alpine.tar  alpine  local  1
# alpine2.tar docker2 latest 0
# alpine3.tar alpine3 local  0
# alpine4.tar alpine4 1.0    1
#
# Other configurable variables:
# CONTAINERS_INSTALL_DIR  : The folder underneath ${WORKDIR} where the docker
#                           images will be stored
#                           (default: "/usr/share/docker/images")
# CONTAINERS_MANIFEST     : The name of the manifest file containing image
#                           parameters, also stored in CONTAINERS_INSTALL_DIR
#                           (default: "containers.manifest")
# CONTAINERS_TAG_DEFAULT  : Use this to change the value that will be used as
#                           contag if no value is provided
#                           (default: "local")
# CONTAINERS_KEEP_DEFAULT : Use this to change the value that will be used for
#                           conkeep if no value is provided
#                           (default: "0")
#

inherit features_check

REQUIRED_DISTRO_FEATURES = "docker"

RDEPENDS:${PN} = "packagegroup-docker-runtime-minimal"

CONTAINER_IMAGE_FILES ??= ""
CONTAINERS_INSTALL_DIR ??= "${datadir}/docker/images"
CONTAINERS_MANIFEST ??= "containers.manifest"
CONTAINERS_TAG_DEFAULT ??= "local"
CONTAINERS_KEEP_DEFAULT ??= "0"

inherit set_src_uri_from_var

SRC_URI_FROM_VAR_NAME = "CONTAINER_IMAGE_FILES"
# Define installation params
SRC_URI_FROM_VAR_MANIFEST_PARAMS = "conname=[basename] \
contag=${CONTAINERS_TAG_DEFAULT} conkeep=${CONTAINERS_KEEP_DEFAULT}"

SRC_URI_FROM_VAR_UNPACK_DIR = "containers"

# Read manifest and install container images
do_install() {
    local archive name tag keep

    if [ -f "${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}/manifest" ]; then

        install -d "${D}${CONTAINERS_INSTALL_DIR}"
        install -m 644 \
            "${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}/manifest" \
            "${D}${CONTAINERS_INSTALL_DIR}/${CONTAINERS_MANIFEST}"

        while read -r archive name tag keep _; do
            [ -f "${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}/${archive}" ] ||
                bbfatal "${archive} does not exist"

            install -m 644 \
                "${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}/${archive}" \
                "${D}${CONTAINERS_INSTALL_DIR}/${archive}"
        done < "${D}${CONTAINERS_INSTALL_DIR}/${CONTAINERS_MANIFEST}"
    fi
}

do_install[vardeps] += "CONTAINER_IMAGE_FILES"

FILES:${PN} += "${CONTAINERS_INSTALL_DIR}"
