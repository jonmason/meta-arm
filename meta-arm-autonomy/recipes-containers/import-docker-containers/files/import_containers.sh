#!/bin/sh

INSTALL_DIR="###CONTAINERS_INSTALL_DIR###"
MANIFEST="${INSTALL_DIR}/###CONTAINERS_MANIFEST###"

INIT_DIR="/etc/init.d"
DOCKER_INIT="docker.init"

find_docker_init() {
    if [ -f "$INIT_DIR/$DOCKER_INIT" ]; then
         $INIT_DIR/$DOCKER_INIT "start"
    else
        echo "ERROR: Couldn't find docker init script! ($INIT_DIR/$DOCKER_INIT)"
        exit 1
    fi
}

is_docker_started() {
    if ! docker info > /dev/null 2>&1; then
        find_docker_init
    fi
}

check_manifest() {
    if [ ! -f ${MANIFEST} ]; then
        echo "No manifest found!"
        exit 1
    fi
}

has_docker_image() {
    docker image inspect "$1" >/dev/null 2>&1
}

start() {
    check_manifest
    is_docker_started

    while read -r archive name tag keep _; do

        CONTAINER_IMAGE_NAME_AND_TAG="${name}:${tag}"

        # Image does not exist and image file exists: Import the image.
        if ! has_docker_image "${CONTAINER_IMAGE_NAME_AND_TAG}" && \
           [ -f "${INSTALL_DIR}/${archive}" ]; then
            echo "Importing ${CONTAINER_IMAGE_NAME_AND_TAG} container image..."
            docker import "${INSTALL_DIR}/${archive}" \
                   "${CONTAINER_IMAGE_NAME_AND_TAG}" 2>&1 || {
                echo "Import ${CONTAINER_IMAGE_NAME_AND_TAG} container image: Failed."
                exit $?
            }
            echo "Import ${CONTAINER_IMAGE_NAME_AND_TAG} container image: Done."

            if [ "${keep}" != "1" ]; then
                rm "${INSTALL_DIR}/${archive}"
            fi
        fi
    done < ${MANIFEST}
}

case "$1" in
    start)
        start && exit 0
        ;;
    *)
        echo "Usage: $0 {start}"
        exit 2
esac

exit $?
