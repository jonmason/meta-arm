# Create a xenguest image containing the kernel with initramfs when
# initramfs is activated
# This is done using kernel-fitimage as model
# To activate this, kernel-xenguest must be added to KERNEL_CLASSES

inherit xenguest-image

# use a local copy to pack all together
XENGUEST_IMAGE_DEPLOY_DIR = "${WORKDIR}/tmp-xenguest"

python __anonymous () {
    # only if xenguest image type is present
    if bb.utils.contains('IMAGE_FSTYPES', 'xenguest', '1', '0', d):
        # only if initramfs bundle is activated
        if d.getVar('INITRAMFS_IMAGE') and d.getVar('INITRAMFS_IMAGE_BUNDLE') == "1":
            if not bb.utils.contains('KERNEL_IMAGETYPES', 'Image', '1', '0', d):
                bb.fatal("xenguest image type with initramfs require Image kernel image type")
            bb.build.addtask('do_assemble_xenguest_initramfs', 'do_deploy', 'do_bundle_initramfs', d)
}

do_assemble_xenguest_initramfs() {
    xenguest_image_clone
    call_xenguest_mkimage partial --xen-kernel=${B}/${KERNEL_OUTPUT_DIR}/Image.initramfs
    rm -f ${B}/${KERNEL_OUTPUT_DIR}/Image-initramfs.xenguest
    call_xenguest_mkimage pack ${B}/${KERNEL_OUTPUT_DIR}/Image-initramfs.xenguest
}
do_assemble_xenguest_initramfs[depends] += "${INITRAMFS_IMAGE}:do_image_complete"

kernel_do_deploy_append() {
    if [ -f "${B}/${KERNEL_OUTPUT_DIR}/Image-initramfs.xenguest" ]; then
        install -m 0644 ${B}/${KERNEL_OUTPUT_DIR}/Image-initramfs.xenguest "$deployDir/Image-${INITRAMFS_NAME}.xenguest"
        ln -snf Image-${INITRAMFS_NAME}.xenguest $deployDir/Image-${INITRAMFS_LINK_NAME}.xenguest
    fi
}
