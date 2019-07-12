# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#
SUMMARY = "Cramfs XIP image type"
DESCRIPTION = "Cramfs XIP type image to add to IMAGE_TYPES"
LICENSE = "MIT"

inherit image_types

do_image_cramfs_xip[depends] += "cramfs-tools-native:do_populate_sysroot"

IMAGE_TYPES += " cramfs-xip"

IMAGE_CMD_cramfs-xip = "mkcramfs -n ${IMAGE_NAME} -X ${IMAGE_ROOTFS} ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.cramfs-xip ${EXTRA_IMAGECMD}"
