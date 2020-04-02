# Create a xenguest image with kernel and filesystem produced by Yocto
# This will create a .xenguest file that the xenguest-manager can use.

inherit xenguest-image deploy

# We are creating our guest in a local subdirectory
# force the value so that we are not impacted if the user is changing it
XENGUEST_IMAGE_DEPLOY_DIR = "${WORKDIR}/tmp-xenguest"

# Name of deployed file (keep standard image name and add .xenguest)
XENGUEST_IMAGE_DEPLOY ??= "${IMAGE_NAME}"

# Deployed file when building with initramfs
XENGUEST_IMAGE_INITRAMFS_DEPLOY ??= "Image-initramfs-${MACHINE}"

# Add kernel XENGUEST_IMAGE_KERNEL from DEPLOY_DIR_IMAGE to image
xenguest_image_add_kernel() {
    srcfile="${1:-}"
    if [ -z "${srcfile}" ]; then
        srcfile="${DEPLOY_DIR_IMAGE}/${XENGUEST_IMAGE_KERNEL}"
    fi
    call_xenguest_mkimage partial --xen-kernel=$srcfile
}

# Add rootfs file to the image
xenguest_image_add_rootfs() {
    call_xenguest_mkimage partial \
        --disk-add-file=${IMGDEPLOYDIR}/${IMAGE_LINK_NAME}.${IMAGE_TYPEDEP_xenguest}:rootfs.${IMAGE_TYPEDEP_xenguest}
}

# Pack xenguest image
xenguest_image_pack() {
    mkdir -p ${IMGDEPLOYDIR}
    rm -f ${IMGDEPLOYDIR}/${XENGUEST_IMAGE_DEPLOY}.xenguest
    call_xenguest_mkimage pack \
        ${IMGDEPLOYDIR}/${XENGUEST_IMAGE_DEPLOY}.xenguest
}

# do_deploy is used for initramfs to pack the kernel initramfs in an image
do_deploy() {
    # Add kernel
    xenguest_image_add_kernel

    # Pack the image in deploydir
    mkdir -p ${DEPLOYDIR}
    rm -f ${DEPLOYDIR}/${XENGUEST_IMAGE_INITRAMFS_DEPLOY}.xenguest
    call_xenguest_mkimage pack \
        ${DEPLOYDIR}/${XENGUEST_IMAGE_INITRAMFS_DEPLOY}.xenguest
}
do_deploy[depends] += "${PN}:do_bootimg_xenguest"
do_deploy[depends] += "virtual/kernel:do_deploy"

#
# Task finishing the bootimg
# We need this task to actually create the symlinks
#
python do_bootimg_xenguest() {
    subtasks = d.getVarFlag('do_bootimg_xenguest', 'subtasks')

    bb.build.exec_func('xenguest_image_clone', d)
    if subtasks:
        for tk in subtasks.split():
            bb.build.exec_func(tk, d)
    bb.build.exec_func('xenguest_image_pack', d)
    bb.build.exec_func('create_symlinks', d)
}
# This is used to add sub-tasks to do_bootimg_xenguest
do_bootimg_xenguest[subtasks] = ""
# Those are required by create_symlinks to find our image
do_bootimg_xenguest[subimages] = "xenguest"
do_bootimg_xenguest[imgsuffix] = "."
do_bootimg_xenguest[depends] += "xenguest-base-image:do_deploy"
# Need to have rootfs so all recipes have deployed their content
do_bootimg_xenguest[depends] += "${PN}:do_rootfs"

# This set in python anonymous after, just set a default value here
IMAGE_TYPEDEP_xenguest ?= "tar"

# We must not be built at rootfs build time because we need the kernel
IMAGE_TYPES_MASKED += "xenguest"
IMAGE_TYPES += "xenguest"

python __anonymous() {
    # Do not do anything if we are not in the want FSTYPES
    if bb.utils.contains_any('IMAGE_FSTYPES', 'xenguest', '1', '0', d):

        # Check the coherency of the configuration
        rootfs_needed = False
        rootfs_file = ''
        kernel_needed = False
        initramfs_needed = False

        rootfs_file = xenguest_image_rootfs_file(d)
        if rootfs_file:
            rootfs_needed = True

        if d.getVar('XENGUEST_IMAGE_KERNEL'):
            kernel_needed = True

        if d.getVar('INITRAMFS_IMAGE'):
            if int(d.getVar('INITRAMFS_IMAGE_BUNDLE')) != 1:
                bb.error("xenguest-fstype: INITRAMFS_IMAGE is set but INITRAMFS_IMAGE_BUNDLE is set to 0.\n")
                bb.fatal("xenguest-fstype: This configuration is not supported by xenguest image type\n")
            initramfs_needed = True

        if initramfs_needed and rootfs_needed:
            bb.warn("xenguest-fstype: Final image will use an initramfs kernel and rootfs in disk.\n")
            bb.warn("xenguest-fstype: rootfs.tar.%s should be removed from XENGUEST_IMAGE_DISK_PARTITIONS.\n")

        if not initramfs_needed and not rootfs_needed and not kernel_needed:
            bb.warn("xenguest-fstype: Generated image will have no kernel and no rootfs.\n")

        bb.build.addtask('do_bootimg_xenguest', 'do_image_complete', None, d)

        if rootfs_needed:
            # tell do_bootimg_xenguest to call add_rootfs
            d.appendVarFlag('do_bootimg_xenguest', 'subtasks', ' xenguest_image_add_rootfs')
            # do_bootimg_xenguest will need the tar file
            d.appendVarFlag('do_bootimg_xenguest', 'depends', ' %s:do_image_tar' % (d.getVar('PN')))
            # set our TYPEDEP to the proper compression
            d.setVar('IMAGE_TYPEDEP_xenguest', 'tar' + (rootfs_file.split('.tar', 1)[1] or ''))

        if kernel_needed:
            if initramfs_needed:
                bb.build.addtask('do_deploy', 'do_build', None, d)
            else:
                # Tell do_bootimg_xenguest to call xenguest_image_add_kernel
                d.appendVarFlag('do_bootimg_xenguest', 'subtasks', ' xenguest_image_add_kernel')
                # we will need kernel do_deploy
                d.appendVarFlag('do_bootimg_xenguest', 'depends', ' virtual/kernel:do_deploy')
}

