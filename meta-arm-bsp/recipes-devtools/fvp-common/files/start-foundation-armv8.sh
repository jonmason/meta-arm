#!/bin/bash
# Script to start a build image using FVP Foundation Platform
#
set -u
set -e

# Get parameters from bitbake configuration
source <(bitbake -e foundation-armv8-native | grep \
    -e "^STAGING_.*_NATIVE=" \
    -e "^DEPLOY_DIR.*=")


# Bitbake image to run
IMAGE_NAME="$(cd $DEPLOY_DIR_IMAGE; ls *-foundation-armv8.manifest | \
    sed -e "s/-foundation-armv8\.manifest//")"

# BL1 and FIP files
BL1_FILE="bl1-fvp.bin"
BL1_ADDR="0x0"
FIP_FILE="fip-fvp.bin"
FIP_ADDR="0x8000000"

# Linux kernel file in deploy_dir and load address
KERNEL_FILE="Image"
KERNEL_ADDR="0x80080000"

# DTB file in deploy_dir and load address
DTB_FILE="foundation-v8-gicv3-psci.dtb"
DTB_ADDR="0x83000000"

# Xen file in deploy_dir and load address
XEN_FILE="xen-foundation-armv8"
XEN_ADDR="0x84000000"

# Disk file in deploy_dir
DISK_FILE=""

# Foundation Platform Executable (Extracted from
# FM000-KT-00035-r11p8-61rel0.tgz from silver.arm.com)
FOUNDATION_PLAT_EXE="Foundation_Platform"

# Foundation Platform arguments
FOUNDATION_PLAT_ARGS=" \
    --cores=4 \
    --secure-memory \
    --use-real-time \
    --gicv3"

# Foundation Platform user arguments
EXTRA_ARGS=""

# Help function
usage() {
    cat <<EOF
Usage $0 [OPTION] [IMAGE_NAME] [FOUNDATION_PLATFORM_ARGS]
Start a generated Yocto Image using Armv8-A Foundation Platform.
This script will execute Foundation_Platform from the PATH.

IMAGE_NAME should be the name of the image to start, this is what you did
build with bitbake, default is 'core-image-minimal' if none is auto-detected.
All extra arguments are passed to Foundation Platform after the IMAGE_NAME.

OPTIONs:
  -h, --help                  displays this help message
  --deploy=[DIR]              use DIR as deploy directory, default is:
                              $DEPLOY_DIR_IMAGE
  --no-bl1                    Don't load a BL1
  --bl1=[NAME]                File name in DEPLOY_DIR_IMAGE to be used for BL1,
                              default is $BL1_FILE.
                              This adds the following argument to the
                              Foundation Platform:
                              --data=$DEPLOY_DIR_IMAGE/NAME@$BL1_ADDR
  --no-fip                    Don't load a FIP
  --fip=[NAME]                File name in DEPLOY_DIR_IMAGE to be used for FIP,
                              default is $FIP_FILE.
                              This adds the following argument to the
                              Foundation Platform:
                              --data=$DEPLOY_DIR_IMAGE/NAME@$FIP_ADDR
  --linux=[NAME]              File name in DEPLOY_DIR_IMAGE to be used
                              as Linux kernel
                              default is $KERNEL_FILE
  --linux-addr=[ADDR]         Address at which Linux kernel should be loaded
                              default is $KERNEL_ADDR
  --dtb=[NAME]                File name in DEPLOY_DIR_IMAGE to be used as DTB
                              default is $DTB_FILE
  --dtb-addr=[ADDR]           Address at which DTB should be loaded
                              default is $DTB_ADDR
  --xen=[NAME]                File name in DEPLOY_DIR_IMAGE to be used as Xen
                              It is only loaded if the file actually exists.
                              default is $XEN_FILE
  --xen-addr=[ADDR]           Address at which Xen should be loaded
                              default is $XEN_ADDR
  --disk=[NAME]               File name in DEPLOY_DIR_IMAGE to be used as disk.
                              It is only loaded if the file actually exists.
                              default is IMAGE_NAME-foundation-armv8.disk.img
EOF
}

# Process command line arguments
for arg in "$@"; do
    case $arg in
        --*=*)
            optarg=$(echo $arg | sed -e "s/.*=//")
            ;;
        *)
            optarg=""
            ;;
    esac

    case $arg in
        -h|-?|--help)
            usage
            exit 0
            ;;
        --deploy=*)
            if [ ! -f $optarg/Image ]
            then
                echo "Invalid argument" >&2
                echo "$optarg is not a valid deploy directory" >&2
                exit 1
            fi
            DEPLOY_DIR_IMAGE=$optarg
            ;;
        --no-bl1)
            BL1_FILE=""
            ;;
        --bl1=*)
            BL1_FILE="$optarg"
            ;;
        --no-fip)
            FIP_FILE=""
            ;;
        --fip=*)
            FIP_FILE="$optarg"
            ;;
        --linux=*)
            LINUX_FILE="$optarg"
            ;;
        --linux-addr=*)
            LINUX_ADDR="$optarg"
            ;;
        --dtb=*)
            DTB_FILE="$optarg"
            ;;
        --dtb-addr=*)
            DTB_ADDR="$optarg"
            ;;
        --xen=*)
            XEN_FILE="$optarg"
            ;;
        --xen-addr=*)
            XEN_ADDR="$optarg"
            ;;
        --disk=*)
            DISK_FILE="$optarg"
            ;;
        *)
            if [ -z "$IMAGE_NAME" ]
            then
                IMAGE_NAME="$arg"
            else
                EXTRA_ARGS="$EXTRA_ARGS $arg"
            fi
            ;;
    esac
done

if [ -z "${BUILDDIR:-}" ]; then
    echo "We are not in a Yocto build project." >&2
    echo "Please source oe-init-build-env first." >&2
    exit 1
fi

if [ -z "${IMAGE_NAME:-}" ]; then
    IMAGE_NAME="core-image-minimal"
fi

if [ -z "${DISK_FILE:-}" ]; then
    DISK_FILE="${IMAGE_NAME}-foundation-armv8.disk.img"
fi

# Add bl1 arg
if [ -n "$BL1_FILE" ]; then
    if [ ! -f $DEPLOY_DIR_IMAGE/$BL1_FILE ]; then
        echo "Could not find bl1 ($BL1_FILE) in $DEPLOY_DIR_IMAGE" >&2
        exit 1
    fi
    FOUNDATION_PLAT_ARGS="$FOUNDATION_PLAT_ARGS \
        --data=$DEPLOY_DIR_IMAGE/$BL1_FILE@$BL1_ADDR"
fi

# Add fip arg
if [ -n "$FIP_FILE" ]; then
    if [ ! -f $DEPLOY_DIR_IMAGE/$FIP_FILE ]; then
        echo "Could not find fip ($FIP_FILE) in $DEPLOY_DIR_IMAGE" >&2
        exit 1
    fi
    FOUNDATION_PLAT_ARGS="$FOUNDATION_PLAT_ARGS \
        --data=$DEPLOY_DIR_IMAGE/$FIP_FILE@$FIP_ADDR"
fi

# Add Linux kernel
if [ -n "$KERNEL_FILE" ]; then
    if [ ! -f $DEPLOY_DIR_IMAGE/$KERNEL_FILE ]; then
        echo "Could not find Linux kernel ($KERNEL_FILE) in \
            $DEPLOY_DIR_IMAGE" >&2
        exit 1
    fi
    FOUNDATION_PLAT_ARGS="$FOUNDATION_PLAT_ARGS \
        --data=$DEPLOY_DIR_IMAGE/$KERNEL_FILE@$KERNEL_ADDR"
fi

# Add DTB
if [ -n "$DTB_FILE" ]; then
    if [ ! -f $DEPLOY_DIR_IMAGE/$DTB_FILE ]; then
        echo "Could not find the DTB ($DTB_FILE) in $DEPLOY_DIR_IMAGE" >&2
        exit 1
    fi
    FOUNDATION_PLAT_ARGS="$FOUNDATION_PLAT_ARGS \
        --data=$DEPLOY_DIR_IMAGE/$DTB_FILE@$DTB_ADDR"
fi

# Add xen if present
if [ -n "$XEN_FILE" -a -f $DEPLOY_DIR_IMAGE/$XEN_FILE ]; then
   FOUNDATION_PLAT_ARGS="$FOUNDATION_PLAT_ARGS \
       --data=$DEPLOY_DIR_IMAGE/$XEN_FILE@$XEN_ADDR"
fi

# Add disk if present
if [ -n "$DISK_FILE" -a -f $DEPLOY_DIR_IMAGE/$DISK_FILE ]; then
    FOUNDATION_PLAT_ARGS="$FOUNDATION_PLAT_ARGS \
        --block-device=$DEPLOY_DIR_IMAGE/$DISK_FILE"
fi

FOUNDATION_PLAT_EXE="${STAGING_BINDIR_NATIVE}/${FOUNDATION_PLAT_EXE}"

echo "$FOUNDATION_PLAT_EXE $FOUNDATION_PLAT_ARGS $EXTRA_ARGS"
$FOUNDATION_PLAT_EXE $FOUNDATION_PLAT_ARGS $EXTRA_ARGS
