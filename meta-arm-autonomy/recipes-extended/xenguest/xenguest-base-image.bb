# Create a xenguest base image
#
# This recipe creates a base image that is then extended by other recipes
# through xenguest-image class.
# xenguest image type is using this as base to add a kernel and a disk image
# to create a guest
#
# The recipe is also adding files in those directories to the xenguest image:
# - ${WORKDIR}/extend/disk-files: all files in this directory will be added to
#   the guest disk files (using --disk-add-file)
# - ${WORKDIR}/extend/files: all files in this directory will be added to the
#   guest xen files (using --xen-add-file)
# - ${WORKDIR}/extend/guest.d: all files in this directory will be added to
#   the xen append configuration files (using --xen-append)
# - ${WORKDIR}/extend/init.[pre|post|d]: all files in those directories will
#   be added to the corresponding init scripts (using --init-[pre|post|script])
# You can bbappend this recipe and put files in ${WORKDIR}/extend to add
# elements to the image.
#

DESCRIPTION = "Xenguest Base Image"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

#
# The following variables can contain SRC_URI compatible entries to add
# files to the xenguest image.
# You can set those variable in local.conf to add one or several files
# For example to add a boot.tar.gz file that has to be downloaded to the file
# useable for disk partition initialisation:
# XENGUEST_IMAGE_SRC_URI_DISK_FILES += "https://www.test.com/files/boot.tar.gz"

# Add disk files
XENGUEST_IMAGE_SRC_URI_DISK_FILES ??= ""

# Add xen files
XENGUEST_IMAGE_SRC_URI_XEN_FILES ??= ""

# Add xen configuration elements
XENGUEST_IMAGE_SRC_URI_XEN_CONFIG ??= ""

# Add pre init script
XENGUEST_IMAGE_SRC_URI_INIT_PRE ??= ""

# Add init script
XENGUEST_IMAGE_SRC_URI_INIT ??= ""

# Add post init script
XENGUEST_IMAGE_SRC_URI_INIT_POST ??= ""

S = "${WORKDIR}"

inherit deploy xenguest-image

# parse XENGUEST_IMAGE_SRC_URI_ variables and add them to SRC_URI
python __anonymous() {
    def parse_extend_variable(d, varname, destdir):
        list = d.getVar(varname)
        if list:
            for entry in list.split():
                #Check the URL
                try:
                    decode = bb.fetch.decodeurl(entry)
                    d.appendVar('SRC_URI', ' ' + entry + ';unpack=0;subdir=extend/' + destdir)
                except:
                    bb.fatal("%s: %s contains an invalid URL:  %s" \
                    % (d.getVar('PF'), varname, entry))

    parse_extend_variable(d, 'XENGUEST_IMAGE_SRC_URI_DISK_FILES', 'disk-files')
    parse_extend_variable(d, 'XENGUEST_IMAGE_SRC_URI_XEN_FILES', 'files')
    parse_extend_variable(d, 'XENGUEST_IMAGE_SRC_URI_XEN_CONFIG', 'guest.d')
    parse_extend_variable(d, 'XENGUEST_IMAGE_SRC_URI_INIT_PRE', 'init.pre')
    parse_extend_variable(d, 'XENGUEST_IMAGE_SRC_URI_INIT', 'init.d')
    parse_extend_variable(d, 'XENGUEST_IMAGE_SRC_URI_INIT_POST', 'init.post')
}

# Make sure we are removing old files before redoing a fetch
do_fetch[cleandirs] += "${WORKDIR}/extend"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_install[noexec] = "1"

add_extend_files() {
    local subdir="$1"
    local cmd="$2"
    local stripdest="${3:-n}"

    if [ -d ${WORKDIR}/extend/$subdir ]; then
        filelist=$(find ${WORKDIR}/extend/$subdir -type f)

        if [ -n "$filelist" ]; then
            for f in $filelist; do
                if [ "$stripdest" = "y" ]; then
                    call_xenguest_mkimage update --$cmd=$f:$(basename $f)
                else
                    call_xenguest_mkimage update --$cmd=$f
                fi
            done
        fi
    fi
}

do_deploy() {
    # Create a new image
    xenguest_image_create

    # Add our extra files if any
    add_extend_files "disk-files" "disk-add-file" "y"
    add_extend_files "files" "xen-add-file" "y"
    add_extend_files "guest.d" "xen-append"
    add_extend_files "init.pre" "init-pre"
    add_extend_files "init.d" "init-script"
    add_extend_files "init.post" "init-post"
}

addtask deploy after do_install before do_build

