# Xenguest Extern Guests
#
# This recipe installs the extern guest files specified in
# ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS into the host image, They are installed
# to the directory XENGUEST_MANAGER_GUEST_DIR
#
# src_uri_parse_var.bbclass is used to parse
# ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS and add the guest paths to the SRC_URI
# to be fetched and unpacked to ${WORKDIR}/${SRC_URI_FROM_VAR_UNPACK_DIR}
#
# Further documentation can be found in documentation/arm-autonomy-quickstart.md,
# in the section named "Include guests directly in the host image"

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

FILES:${PN} += "${XENGUEST_MANAGER_GUEST_DIR}"

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
