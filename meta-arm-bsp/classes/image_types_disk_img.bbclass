# Defines the disk.img image type

#
# Add an image type 'disk.img' which creates a disk image
# with up to 4 partitions
#
# For partition 1 (replace 1 by 2 for partition 2, and so on for 3 and 4):
#
# * DISK_IMG_PARTITION1_SIZE is the partition size in MB (1024 is 1 GB)
#
# * DISK_IMG_PARTITION1_FSTYPE is the file system to format the partition with.
#   We support only ext files systems (ext2, ext3 and ext4)
#   If this is empty, the partition will not be formated.
#
# * DISK_IMG_PARTITION1_CONTENT is the content to put in the filesystem.
#   Only 'rootfs' is supported and will create a partition with the Yocto
#   root filesystem.
#

# Default values for partition 1
DISK_IMG_PARTITION1_SIZE ??= "2048"
DISK_IMG_PARTITION1_FSTYPE ??= "ext4"
DISK_IMG_PARTITION1_CONTENT ??= "rootfs"

# Default values for partition 2
DISK_IMG_PARTITION2_SIZE ??= "0"
DISK_IMG_PARTITION2_FSTYPE ??= "ext2"
DISK_IMG_PARTITION2_CONTENT ??= ""

# Default values for partition 3
DISK_IMG_PARTITION3_SIZE ??= "0"
DISK_IMG_PARTITION3_FSTYPE ??= "ext4"
DISK_IMG_PARTITION3_CONTENT ??= ""

# Default values for partition 4
DISK_IMG_PARTITION4_SIZE ??= "0"
DISK_IMG_PARTITION4_FSTYPE ??= "ext4"
DISK_IMG_PARTITION4_CONTENT ??= ""

# Default disk sector size
DISK_IMG_SECTOR_SIZE ??= "512"

# We need mkfs.ext and parted tools to create our image (dd is always there)
do_image_disk_img[depends] += "e2fsprogs-native:do_populate_sysroot \
    parted-native:do_populate_sysroot"

DISK_IMG_FILE = "${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.disk.img"

# Create one disk partition
disk_img_createpart() {
    local imagefile="$1"
    local start="$2"
    local size="$3"
    local fstype="${4:-}"
    local content="${5:-}"
    local formatargs=""

    set -x

    rm -f $imagefile

    # Create the partition image
    dd if=/dev/zero of=$imagefile bs=${DISK_IMG_SECTOR_SIZE} count=0 \
        seek=$(expr $size / ${DISK_IMG_SECTOR_SIZE})

    if [ -n "$fstype" ]; then
        case $content in
            rootfs)
                formatargs=" -d ${IMAGE_ROOTFS}"
                ;;
            boot)
                echo "Unsupported"
                exit 1
                ;;
            *)
        esac

        # Create the file system (with content if needed)
        mkfs.$fstype -F $imagefile $formatargs
    fi

    cat $imagefile >> ${DISK_IMG_FILE}

    # Add the partition to the partition table
    parted -s ${DISK_IMG_FILE} unit B mkpart primary $start \
        $(expr $start + $realsize - 1)
}

disk_img_create () {
    local currpos
    local realsize

    set -x

    currpos=${DISK_IMG_SECTOR_SIZE}

    # Create reserved part for partition table (1MB)
    dd if=/dev/zero of=${DISK_IMG_FILE} bs=${DISK_IMG_SECTOR_SIZE} count=0 \
        seek=1

    parted -s ${DISK_IMG_FILE} mklabel msdos

    if [ ${DISK_IMG_PARTITION1_SIZE} -ne 0 ]; then

        # Reduce the first block size of one sector to make space
        # for the partition table
        realsize=$(expr ${DISK_IMG_PARTITION1_SIZE} \* 1024 \* 1024 \
            - ${DISK_IMG_SECTOR_SIZE})

        # Create the partition
        disk_img_createpart ${WORKDIR}/part1.img $currpos $realsize \
            "${DISK_IMG_PARTITION1_FSTYPE}" "${DISK_IMG_PARTITION1_CONTENT}"

        currpos=$(expr $currpos + $realsize)
    fi

    if [ ${DISK_IMG_PARTITION2_SIZE} -ne 0 ]; then
        # Partition size
        realsize=$(expr ${DISK_IMG_PARTITION2_SIZE} \* 1024 \* 1024)

        # Create the partition
        disk_img_createpart ${WORKDIR}/part2.img $currpos $realsize \
            "${DISK_IMG_PARTITION2_FSTYPE}" "${DISK_IMG_PARTITION2_CONTENT}"

        currpos=$(expr $currpos + $realsize)

    fi

    if [ ${DISK_IMG_PARTITION3_SIZE} -ne 0 ]; then
        # Partition size
        realsize=$(expr ${DISK_IMG_PARTITION3_SIZE} \* 1024 \* 1024)

        # Create the partition
        disk_img_createpart ${WORKDIR}/part3.img $currpos $realsize \
            "${DISK_IMG_PARTITION3_FSTYPE}" "${DISK_IMG_PARTITION3_CONTENT}"

        currpos=$(expr $currpos + $realsize)

    fi
    if [ ${DISK_IMG_PARTITION4_SIZE} -ne 0 ]; then
        # Partition size
        realsize=$(expr ${DISK_IMG_PARTITION4_SIZE} \* 1024 \* 1024)

        # Create the partition
        disk_img_createpart ${WORKDIR}/part4.img $currpos $realsize \
            "${DISK_IMG_PARTITION4_FSTYPE}" "${DISK_IMG_PARTITION4_CONTENT}"

        currpos=$(expr $currpos + $realsize)

    fi
}

IMAGE_CMD_disk.img = "disk_img_create"
IMAGE_TYPES += "disk.img"

