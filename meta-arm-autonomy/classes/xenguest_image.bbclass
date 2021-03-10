# This class must be used to create, extend or pack a xenguest image.
# It is using xenguest-mkimage tool to do operations

DEPENDS += "xenguest-mkimage-native"

#
# Xenguest image parameters
# All the following parameters can be modified in local.conf or on recipes
# inheriting this class
#

# Guest memory size in MB
XENGUEST_IMAGE_MEMORY_SIZE ??= "512"

# Guest number of vcpus
XENGUEST_IMAGE_NUM_VCPUS ??= "1"

# Guest auto boot during init, set to 1 to have guest started during init or
# to 0 if the guest should not be auto started
XENGUEST_IMAGE_AUTOBOOT ??= "1"

# Partition containing the root file system
# Xen will actually add root=${XENGUEST_IMAGE_ROOT} to your guest kernel
# command line
# You can let this empty if the root filesystem is specified in an other way
# and have root= option added to the command line for example or if you don't
# need a root filesystem mounted for your guest (initrd for example)
XENGUEST_IMAGE_ROOT ??= "/dev/xvda1"

# Guest kernel command line arguments
XENGUEST_IMAGE_CMDLINE ??= "earlyprintk=xenboot console=hvc0 rw"

# Extra commands to add to xenguest_image when creating the image
XENGUEST_IMAGE_EXTRA_CMD ??= ""

# Kernel binary
# This value is used by the xenguest image type but is declared here to have
# all variables in the same place
# If this value is empty no kernel will be added to the image
XENGUEST_IMAGE_KERNEL ??= "Image"

# Size of the disk to create (if 0 no disk will be created and rootfs will not
# be included in the xenguest image)
XENGUEST_IMAGE_DISK_SIZE ??= "${@ '4' if not d.getVar('INITRAMFS_IMAGE') else '0'}"

# set empty partition to be used by xenguest-manager for this image
XENGUEST_IMAGE_DISK_DEVICE ??= ""

#
# XENGUEST_IMAGE_DISK_PARTITIONS is used to describe the partitions to setup
# and their content.
# It must be set to a space separated list of entries with each entry having
# the format num:sz:[fs]:[file] where:
# - num is a partition number
# - sz is the partition size in MB or GB(default), e.g 1000M or 1[G]
# - fs is optional filesystem to use for the partition
# - file is optionally pointing to a file to use as content of the partition
#   Please check image_types_xenguest.bbclass for rootfs handling of files
#
# Default value creates a partition 1 using the full disk, formated with ext4
# and containing the root filesystem produced by Yocto
XENGUEST_IMAGE_DISK_PARTITIONS ??= "1:${XENGUEST_IMAGE_DISK_SIZE}:ext4:rootfs.tar.gz"

# XENGUEST_IMAGE_NETWORK_TYPE can be set to "bridge", "nat" or "none".
# The "bridge" type will share the physical eth interface from dom0 with the
# domU. This will allow the domU to have access to the external network.
# The "nat" type will setup a virtual network between dom0 and domU and also
# configure and run the kea dhcp4 server on dom0 to serve the domU.
# The "none" type will not affect any networking setting between on dom0 and
# domU.
XENGUEST_IMAGE_NETWORK_TYPE ??= "bridge"

# Sub-directory in wich the guest is created. This is create in deploy as a
# subdirectory and must be coherent between all components using this class so
# it must only be modified from local.conf if needed
XENGUEST_IMAGE_DEPLOY_SUBDIR ?= "xenguest"

# Directory in which the xenguest should be deployed
# a sub-directory named ${XENGUEST_IMAGE_DEPLOY_SUBDIR} will be created there.
# This should be set to:
# - ${DEPLOYDIR} (default) if creating or extending the xenguest for a normal
#   recipe.
# - something in ${WORKDIR} if you need to clone and manipulate an image
XENGUEST_IMAGE_DEPLOY_DIR ??= "${DEPLOYDIR}"

# These vars are used by image_types_xenguest.bbclass to generate the
# xenguest.env file. In a recipe that inherits this class and extra variables
# that should be included in xenguest.env need to be added to
# XENGUEST_IMAGE_VARS_EXTRA
XENGUEST_IMAGE_VARS ?= "\
 MACHINE DISTRO DISTRO_VERSION DISTRO_FEATURES TUNE_FEATURES TARGET_FPU \
 IMAGE_FEATURES INITRAMFS_IMAGE_BUNDLE INITRAMFS_IMAGE \
 XENGUEST_IMAGE_MEMORY_SIZE XENGUEST_IMAGE_NUM_VCPUS XENGUEST_IMAGE_AUTOBOOT \
 XENGUEST_IMAGE_ROOT XENGUEST_IMAGE_CMDLINE XENGUEST_IMAGE_EXTRA_CMD \
 XENGUEST_IMAGE_KERNEL XENGUEST_IMAGE_DISK_SIZE XENGUEST_IMAGE_DISK_DEVICE \
 XENGUEST_IMAGE_DISK_PARTITIONS XENGUEST_IMAGE_NETWORK_TYPE"

#
# Wrapper to call xenguest-mkimage
# It is using XENGUEST_IMAGE_DEPLOY_DIR and XENGUEST_IMAGE_DEPLOY_SUBDIR
# to find the image to operate on
#
# Usage: call_xenguest_mkimage [operation] [args]
call_xenguest_mkimage() {
    local cmd="${1}"
    local img="${XENGUEST_IMAGE_DEPLOY_DIR}/${XENGUEST_IMAGE_DEPLOY_SUBDIR}"
    shift

    echo "xenguest-mkimage $cmd $img $@"
    xenguest-mkimage $cmd $img $@
}

#
# Create an initial xenguest image.
# This is a task which must be added in a recipe inheriting deploy
# It is using XENGUEST_IMAGE_MEMORY_SIZE, XENGUEST_IMAGE_NUM_VCPUS,
#  XENGUEST_IMAGE_AUTOBOOT, XENGUEST_IMAGE_ROOT, XENGUEST_IMAGE_EXTRA_CMD,
#  XENGUEST_IMAGE_CMDLINE, XENGUEST_IMAGE_DISK_SIZE and
#  XENGUEST_IMAGE_DISK_PARTITIONS to customize the initial guest
#
xenguest_image_create() {
    if [ -z "${XENGUEST_IMAGE_DEPLOY_DIR}" -o \
        -z "${XENGUEST_IMAGE_DEPLOY_SUBDIR}" ]; then
        die "Configuration error: XENGUEST_IMAGE_DEPLOY_DIR or XENGUEST_IMAGE_DEPLOY_SUBDIR is empty"
    fi

    rm -rf ${XENGUEST_IMAGE_DEPLOY_DIR}/${XENGUEST_IMAGE_DEPLOY_SUBDIR}

    mkdir -p ${XENGUEST_IMAGE_DEPLOY_DIR}/${XENGUEST_IMAGE_DEPLOY_SUBDIR}

    # Create the image
    call_xenguest_mkimage create --xen-memory=${XENGUEST_IMAGE_MEMORY_SIZE} \
        --xen-vcpus=${XENGUEST_IMAGE_NUM_VCPUS} \
        --xen-root=${XENGUEST_IMAGE_ROOT} \
        ${XENGUEST_IMAGE_EXTRA_CMD}

    # add command line
    if [ -n "${XENGUEST_IMAGE_CMDLINE}" ]; then
        call_xenguest_mkimage update --xen-clean-extra
        for arg in ${XENGUEST_IMAGE_CMDLINE}; do
            call_xenguest_mkimage update --xen-extra=$arg
        done
    fi

    # create disk if needed
    disksize="${XENGUEST_IMAGE_DISK_SIZE}"
    case ${disksize:=0} in
        0|0M|0G)
            ;;
        *)
            # setup disk size
            call_xenguest_mkimage update --disk-reset-config --disk-size=$disksize

            diskparts="${XENGUEST_IMAGE_DISK_PARTITIONS}"
            if [ -n "$diskparts" ]; then
                for arg in $diskparts; do
                    call_xenguest_mkimage update --disk-add-part=$arg
                done
            fi
            diskdevice="${XENGUEST_IMAGE_DISK_DEVICE}"
            if [ -n "$diskdevice" ]; then
                call_xenguest_mkimage update --disk-device="${diskdevice}"
            fi

            ;;
    esac


    if [ "${XENGUEST_IMAGE_AUTOBOOT}" = "1" ]; then
        call_xenguest_mkimage update --set-param=GUEST_AUTOBOOT=1
    else
        call_xenguest_mkimage update --set-param=GUEST_AUTOBOOT=0
    fi

    if [ -n "${XENGUEST_IMAGE_NETWORK_TYPE}" ]; then
        call_xenguest_mkimage update --set-param=XENGUEST_NETWORK_TYPE="${XENGUEST_IMAGE_NETWORK_TYPE}"
    else
        call_xenguest_mkimage update --set-param=XENGUEST_NETWORK_TYPE="none"
    fi
}

XENGUEST_ENV_STAGING_DIR ??= "${STAGING_DIR}/${MACHINE}/xenguestenv"

# Create an intermediary file containing all variables used to by a
# particular recipe that inherits this class

# File will contain the values of all variables listed in:
#   XENGUEST_IMAGE_VARS_EXTRA
python do_deploy_xenguestenv () {
    xenguest_vars = d.getVar('XENGUEST_IMAGE_VARS_EXTRA')
    if not xenguest_vars:
        return

    outdir = d.getVar('XENGUEST_ENV_STAGING_DIR')

    # Writes file to tmp/sysroots/${MACHINE}/xenguestenv/ by default
    filename = os.path.basename(d.getVar('FILE')) + '.xenguestenv'
    with open(os.path.join(outdir, filename), 'w') as envf:
        for var in xenguest_vars.split():
            value = d.getVar(var)
            if value:
                # Write value only if set
                envf.write('%s="%s"\n' % (var, " ".join(value.split())))
        envf.close()
}

# Since the intermediary file is deleted by do_merge_xenguestenv it
# must be re-created every time
do_deploy_xenguestenv[vardeps] += "${XENGUEST_IMAGE_VARS_EXTRA}"
do_deploy_xenguestenv[dirs] = "${XENGUEST_ENV_STAGING_DIR}"

addtask deploy_xenguestenv before do_populate_sysroot

# Clone the current xenguest from deploy to manipulate it locally
# This is required if you need to change things before packing an image
# To set the local directory where to clone you must set
# XENGUEST_IMAGE_DEPLOY_DIR if you don't want to use do_deploy to modify the
# image
#
xenguest_image_clone() {
    if [ -z "${XENGUEST_IMAGE_DEPLOY_DIR}" -o \
        -z "${XENGUEST_IMAGE_DEPLOY_SUBDIR}" ]; then
        die "Configuration error: XENGUEST_IMAGE_DEPLOY_DIR or XENGUEST_IMAGE_DEPLOY_SUBDIR is empty"
    fi

    if [ ! -f ${DEPLOY_DIR_IMAGE}/${XENGUEST_IMAGE_DEPLOY_SUBDIR}/guest.cfg ]; then
        die "xenguest_image: ${DEPLOY_DIR_IMAGE}/${XENGUEST_IMAGE_DEPLOY_SUBDIR} does not contain a valid guest"
    fi

    rm -rf ${XENGUEST_IMAGE_DEPLOY_DIR}/${XENGUEST_IMAGE_DEPLOY_SUBDIR}
    mkdir -p ${XENGUEST_IMAGE_DEPLOY_DIR}
    cp -rf ${DEPLOY_DIR_IMAGE}/${XENGUEST_IMAGE_DEPLOY_SUBDIR} \
        ${XENGUEST_IMAGE_DEPLOY_DIR}/${XENGUEST_IMAGE_DEPLOY_SUBDIR}
}

# Helper function to retrieve rootfs file if present in one partition
# This can return an empty string or rootfs.tar[.COMP]
def xenguest_image_rootfs_file(d):
    disksize = d.getVar('XENGUEST_IMAGE_DISK_SIZE')
    # if disksize is 0, we don't create anything
    if not disksize or disksize == '0':
        return ""
    # Find first partition with file=rootfs.tar*
    partlist = d.getVar('XENGUEST_IMAGE_DISK_PARTITIONS')
    if partlist:
        for partdesc in partlist.split():
            partelems = partdesc.split(':', 3)
            if partelems[3]:
                if partelems[3].startswith('rootfs.tar'):
                    return partelems[3]
    return ""
