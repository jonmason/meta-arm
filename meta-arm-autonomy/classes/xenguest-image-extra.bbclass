# This class must be used to extend the xenguest image
# It provides variables to add init scripts, a dtb, xen files or disk files.
#
# The class is extending deploy function so you recipe must inherit deploy and
# have a do_deploy function (even if it is empty)

# Use standard xenguest-image
inherit xenguest-image

# Add a DTB file for the guest
# Only one file should be added, if this is set multiple times or in several
# recipes, the last recipe setting it will prevail.
XENGUEST_EXTRA_DTB ??= ""

# Append something to the guest xen configuration
# All files here will be merged together in the final xen configuration
# This can contain several files or be used in several recipes
XENGUEST_EXTRA_XENCONFIG ??= ""

# Add a xenguest init, init-pre or init-post script
XENGUEST_EXTRA_INIT_PRE ??= ""
XENGUEST_EXTRA_INIT ??= ""
XENGUEST_EXTRA_INIT_POST ??= ""

# Add xenguest files, (to be used in extra xen config for example)
# several files may be added, space separated, the path will be kept on the
# generated xenguest image (if dir1/file1 is added, it can be used as
# dir1/file1 file in the xen configuration).
XENGUEST_EXTRA_FILES ??= ""

# Add xenguest disk files (to be used as disk partition content)
# several files may be added, space separated, the path will be kept on the
# generated xenguest image (if dir1/file1 is added, it can be used as
# dir1/file1 file in the disk content parameters).
XENGUEST_EXTRA_DISK_FILES ??= ""

do_deploy_append() {
    if [ -z "${XENGUEST_IMAGE_DEPLOY_DIR}" -o \
        -z "${XENGUEST_IMAGE_DEPLOY_SUBDIR}" ]; then
        die "Configuration error: XENGUEST_IMAGE_DEPLOY_DIR or XENGUEST_IMAGE_DEPLOY_SUBDIR is empty"
    fi
    rm -rf ${XENGUEST_IMAGE_DEPLOY_DIR}/${XENGUEST_IMAGE_DEPLOY_SUBDIR}
    mkdir -p ${XENGUEST_IMAGE_DEPLOY_DIR}/${XENGUEST_IMAGE_DEPLOY_SUBDIR}

    if [ -n "${XENGUEST_EXTRA_DTB}" ]; then
        if [ ! -f ${XENGUEST_EXTRA_DTB} ]; then
            die "xenguest-image: DTB file ${XENGUEST_EXTRA_DTB} does not exist"
        fi
        call_xenguest_mkimage partial --xen-device-tree=${XENGUEST_EXTRA_DTB}
    fi

    if [ -n "${XENGUEST_EXTRA_XENCONFIG}" ]; then
        for f in ${XENGUEST_EXTRA_XENCONFIG}; do
            if [ ! -f $f ]; then
                die "xenguest-image: Xen config $f does not exist"
            fi
            call_xenguest_mkimage partial --xen-append=$f
        done
    fi

    if [ -n "${XENGUEST_EXTRA_INIT_PRE}" ]; then
        if [ ! -f ${XENGUEST_EXTRA_INIT_PRE} ]; then
            die "xenguest-image: Init script ${XENGUEST_EXTRA_INIT_PRE} does not exist"
        fi
        call_xenguest_mkimage partial --init-pre=${XENGUEST_EXTRA_INIT_PRE}
    fi

    if [ -n "${XENGUEST_EXTRA_INIT}" ]; then
        if [ ! -f ${XENGUEST_EXTRA_INIT} ]; then
            die "xenguest-image: Init script ${XENGUEST_EXTRA_INIT} does not exist"
        fi
        call_xenguest_mkimage partial --init-script=${XENGUEST_EXTRA_INIT}
    fi

    if [ -n "${XENGUEST_EXTRA_INIT_POST}" ]; then
        if [ ! -f ${XENGUEST_EXTRA_INIT_POST} ]; then
            die "xenguest-image: Init script ${XENGUEST_EXTRA_INIT_POST} does not exist"
        fi
        call_xenguest_mkimage partial --init-post=${XENGUEST_EXTRA_INIT_POST}
    fi

    if [ -n "${XENGUEST_EXTRA_FILES}" ]; then
        for f in ${XENGUEST_EXTRA_FILES}; do
            if [ ! -f $f ]; then
                die "xenguest-image: Xen file $f does not exist"
            fi
            call_xenguest_mkimage partial --xen-add-file=$f
        done
    fi

    if [ -n "${XENGUEST_EXTRA_DISK_FILES}" ]; then
        for f in ${XENGUEST_EXTRA_DISK_FILES}; do
            if [ ! -f $f ]; then
                die "xenguest-image: Disk file $f does not exist"
            fi
            call_xenguest_mkimage partial --disk-add-file=$f
        done
    fi
}
# Need to have xenguest-image tool
do_deploy[depends] += "xenguest-base-image:do_deploy"

