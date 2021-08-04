# Extra machine settings for fvp-base

# FVP uses vda as hard drive and partition 1 is the
# default rootfs, so use vda2 for guest lvm
XENGUEST_MANAGER_VOLUME_DEVICE ?= "/dev/vda2"

# We need to extend the wks search path to be able to find the wks file set in
# ARM_AUTONOMY_WKS_FILE.
WKS_SEARCH_PATH:prepend := "${ARM_AUTONOMY_ARM_BSP_DYNAMIC_DIR}/wic:"

ARM_AUTONOMY_WKS_FILE ?= "arm-autonomy-fvp-base-disk.wks.in"
# set wks file only if INITRAMFS_IMAGE_BUNDLE is not set
WKS_FILE = "${@bb.utils.contains('INITRAMFS_IMAGE_BUNDLE', '1', '',\
                                 '${ARM_AUTONOMY_WKS_FILE}', d)}"

XEN_FILE ?= "xen-fvp-base"
DTB_FILE ?= "${@ get_xen_dtb_filename(d)}"
XEN_ADDR ?= "0x84000000"
DTB_ADDR ?= "0x83000000"

FVP_DATA    += "cluster0.cpu0=${DEPLOY_DIR_IMAGE}/${XEN_FILE}@${XEN_ADDR} \
                cluster0.cpu0=${DEPLOY_DIR_IMAGE}/${DTB_FILE}@${DTB_ADDR}"

# Set the wks guest partition size and unit. It must be aligned with the sum of
# all XENGUEST_IMAGE_DISK_SIZE set for the guests. By default, LVM2 metadata is
# 1 MiB per physical volume, hence it needs to be taken into account when
# setting GUEST_PART_SIZE. The XENGUEST_IMAGE_DISK_SIZE default value is 4GiB.
GUEST_PART_SIZE ?= "4097"
GUEST_PART_SIZE_UNIT ?= "M"

XENGUEST_NETWORK_BRIDGE_MEMBERS ?= "eth0"

# This function uses the "KERNEL_DEVICETREE" variable and manipulates it to
# return the xen kernel device tree file name.
def get_xen_dtb_filename(d):
    kernel_dtb_filename = d.getVar('KERNEL_DEVICETREE',d)
    xen_dtb_filename = os.path.splitext(os.path.basename(kernel_dtb_filename))[0] + '-xen.dtb'
    return xen_dtb_filename

