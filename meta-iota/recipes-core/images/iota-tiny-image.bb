# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2018 Linaro, LLC
# Copyright (c) 2018 ARM Limited
#
# Iota Recipe to build tiny minimal image
#

SUMARY = "Iota Tiny Minimal Image"
DESCRIPTION = "Tiny Linux image for Iota Distribution"
LICENSE = "MIT"
DEPENDS += "u-boot-mkimage-native"

IMAGE_LINGUAS = " "
IMAGE_FEATURES += "debug-tweaks"

inherit core-image

KERNEL_IMAGETYPE = "zImage"

# Remove Partition table if wic image is generated
do_cleanup_partition_table() {
       echo "check if partition table exits in wic image"
       header=$(head -c 4  ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.wic | md5sum -b | cut -d ' ' -f1)

       if [ ${header}=="d9a7c187f1dc40d183b645f61daa500f" ]; then
       	  echo "remove partition table from wic image"
          tail -c +1025 ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.wic > ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.img
          mv ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.img ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.wic
       fi

	#remove ramfs from previoes stage
	rm -rf ${DEPLOY_DIR_IMAGE}/${IMAGE_BASENAME}-${MACHINE}.cpio.gz
}
addtask do_cleanup_partition_table after do_image_wic before do_image_complete


do_image_make_ramfs() {
        echo "adding uboot header to cpio.gz"
        mkimage -A arm -O linux -C none -T ramdisk -n ramdisk -a 0x84000000 -e 0x84000000 -n "Iota Ramdisk" -d  ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.cpio.gz ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.initramfs.cpio.gz
        cp -rf ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.initramfs.cpio.gz ${DEPLOY_DIR_IMAGE}/${IMAGE_BASENAME}-${MACHINE}.cpio.gz
        mv ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.initramfs.cpio.gz ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.cpio.gz
}

do_image_make_ramfs_corstone700() {
	echo "uboot header not required for corstone700"
	cp -f ${IMGDEPLOYDIR}/${IMAGE_BASENAME}-${MACHINE}.cpio.gz ${DEPLOY_DIR_IMAGE}/${IMAGE_BASENAME}-${MACHINE}.cpio.gz
}

addtask do_image_make_ramfs after do_image_cpio before do_image_wic
