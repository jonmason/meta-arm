# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2019 Linaro, LLC
# Copyright (c) 2019 Arm Limited
#
# Iota Recipe to build tiny minimal image
#

SUMARY = "Iota Tiny Minimal Image"
DESCRIPTION = "Tiny Linux image for Iota Distribution"
LICENSE = "MIT"

IMAGE_LINGUAS = " "
IMAGE_FEATURES += "debug-tweaks"
IMAGE_FSTYPES += " wic"
DEPENDS += "u-boot-mkimage-native"

inherit core-image

# Remove Partition table if wic image is generated
do_cleanup_partition_table() {
       echo "check if partition table exits in wic image"
       header=$(head -c 4  ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.wic | md5sum -b | cut -d ' ' -f1)

       if [ ${header}=="d9a7c187f1dc40d183b645f61daa500f" ]; then
                 echo "remove partition table from wic image"
          tail -c +1025 ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.wic > ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.img
          mv ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.img ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.wic
       fi
}
addtask do_cleanup_partition_table after do_image_wic before do_image_complete

do_image_make_ramfs() {
        echo "adding uboot header to cpio.gz"
        mkimage -A arm -O linux -C none -T ramdisk -n ramdisk -a 0x84000000 -e 0x84000000 -n "Iota Ramdisk" -d  ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.cpio.gz ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.initramfs.cpio.gz
        cd ${IMGDEPLOYDIR}; ln -s ${IMAGE_NAME}.rootfs.initramfs.cpio.gz ${IMAGE_LINK_NAME}.initramfs.cpio.gz
}

do_image_make_ramfs_corstone700() {
	echo "u-boot not present in corstone700"
}

addtask do_image_make_ramfs after do_image_cpio before do_image_wic
