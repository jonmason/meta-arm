#!/bin/sh

CONTAINER_IMAGE_FILE="###CONTAINER_IMAGE_FILE###"
CONTAINER_IMAGE_NAME_AND_TAG="###CONTAINER_IMAGE_NAME_AND_TAG###"
CONTAINER_IMAGE_FILE_KEEP="###CONTAINER_IMAGE_FILE_KEEP###"

has_docker_image() {
    docker image inspect "$1" >/dev/null 2>&1
}

start() {
    # Image does not exist and image file exists: Import the image.
    if ! has_docker_image ${CONTAINER_IMAGE_NAME_AND_TAG} && \
       [ -f "/usr/share/docker/images/${CONTAINER_IMAGE_FILE}" ]; then
        echo "Importing ${CONTAINER_IMAGE_NAME_AND_TAG} container image..."
        docker import \
               /usr/share/docker/images/${CONTAINER_IMAGE_FILE} \
               ${CONTAINER_IMAGE_NAME_AND_TAG} 2>&1 || {
            echo "Import ${CONTAINER_IMAGE_NAME_AND_TAG} container image: Failed."
            exit $?
        }
        echo "Import ${CONTAINER_IMAGE_NAME_AND_TAG} container image: Done."

        if [ "${CONTAINER_IMAGE_FILE_KEEP}" != "1" ]; then
            rm /usr/share/docker/images/${CONTAINER_IMAGE_FILE}
        fi
    fi
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
