# Xenguest Extern Guests
#
# This recipe installs the extern guest files specified in
# ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS into the host image, They are installed
# to the directory XENGUEST_MANAGER_GUEST_DIR
#
# src_uri_parse_var.bbclass is used to parse
# ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS
#
# There are 4 supported formats for ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS
# entries:
#
# - http/https url
#   - "https://[url]:[port]/foo.xenguest;md5sum=..."
#
# - file:// absolute local path from root
#   - "file:///xenguests/bar.xenguest"
#
# - file:// path relative to FILESEXTRAPATHS
#  - "file://relative/baz.xenguest"
#
# - plain absolute local path from root
#   - "/xenguests/absolute/xyzzy.xenguest"
#
# It is not recommended to use other yocto URL types, as they may result in
# undefined behaviour.
#
# A semicolon seperated list of install arguments can follow each image path:
# - guestname  : the name that will be attached when the image is imported
#                (default: [filename, without extension])
# - guestcount : the number of copies of the guest to install, with
#                incrementing numbers appended to the name
#                (default: 1)
#
# Any other arguments, for example an md5sum, will be assumed to be fetch
# arguments, and will be kept when the path is added to the SRC_URI
#
# e.g.  ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS = "\
# https://[url]:[port]/base.xenguest;md5sum=[checksum];guestname=http \
# file:///guests/base.xenguest;guestname=file_abs \
# file://foo/base.xenguest;guestname=file_rel;guestcount=2 \
# /guests/foo/bar/base.xenguest;guestname=no_fetcher \ "
#
# Documentation for setting up a multiconfig build can be found in:
# meta-arm-autonomy/documentation/arm-autonomy-multiconfig.md

DESCRIPTION = "Xenguest Extern Guests"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Global value of XENGUEST_MANAGER_GUEST_DIR set here
require conf/xenguest.conf

ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS ??= ""

# Parse the variable ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS for xenguest files,
# unpack them to SRC_URI_FROM_VAR_UNPACK_DIR and create a manifest file
# containing each of SRC_URI_FROM_VAR_MANIFEST_PARAMS for each entry
inherit set_src_uri_from_var
SRC_URI_FROM_VAR_NAME = "ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS"
SRC_URI_FROM_VAR_MANIFEST_PARAMS= "guestname=[basename] guestcount=1"
SRC_URI_FROM_VAR_UNPACK_DIR = "xenguests"

# Unnecessary tasks
do_compile[noexec] = "1"
do_configure[noexec] = "1"
do_patch[noexec] = "1"

# Install guest files to XENGUEST_MANAGER_GUEST_DIR
do_install() {

    local guestfile guestname guestcount

    if [ -f "${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}/manifest" ]; then

        install -d "${D}${XENGUEST_MANAGER_GUEST_DIR}"

        # Iterate over manifest file containing parameters
        while read -r guestfile guestname guestcount _; do
            [ -f "${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}/${guestfile}" ] ||
                bbfatal "${guestfile} does not exist"

            install -m 644 \
                "${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}/${guestfile}" \
                "${D}${XENGUEST_MANAGER_GUEST_DIR}/${guestname}.xenguest"

            # Create symlinks for duplicate guests, appending numbers to
            # guestname
            for i in `seq 2 $guestcount`
            do
                ln -s -r \
                    "${D}${XENGUEST_MANAGER_GUEST_DIR}/${guestname}.xenguest" \
                    "${D}${XENGUEST_MANAGER_GUEST_DIR}/${guestname}$i.xenguest"
            done

        done < "${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}/manifest"
    fi
}

do_install[vardeps] += "ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS"

FILES_${PN} += "${XENGUEST_MANAGER_GUEST_DIR}"

# In a multiconfig build this variable will hold a dependency string, which
# differs based on whether the guest has initramfs or not.  It may have a space
# seperated list of dependency strings if mulitple guest types are configured
MC_DOIMAGE_MCDEPENDS ?= ""
# Example value: mc:host:guest:core-image-minimal:do_merge_xenguestenv

# In a multiconfig build the host task 'do_image' has a dependency on
# multiconfig guest.  This ensures that the guest image file already exists
# when it is needed by the host
DO_IMAGE_MCDEPENDS := "${@ '${MC_DOIMAGE_MCDEPENDS}' \
if d.getVar('BBMULTICONFIG') else ''}"

# Apply mc dependency. Empty string if multiconfig not enabled
do_fetch[mcdepends] += "${DO_IMAGE_MCDEPENDS}"
