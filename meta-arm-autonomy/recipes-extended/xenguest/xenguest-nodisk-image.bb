# Create a xenguest image with kernel but no rootfs or an external rootfs
DESCRIPTION = "Xenguest No Disk Image"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

S = "${WORKDIR}"

inherit deploy xenguest-image

# Name of the file we create in deploy
XENGUEST_IMAGE_NODISK_DEPLOY = "xenguest-nodisk-image.xenguest"

# use a local copy to pack all together
XENGUEST_IMAGE_DEPLOY_DIR = "${WORKDIR}/tmp-xenguest"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_install[noexec] = "1"

do_deploy() {
    xenguest_image_clone

    # Add kernel to the image
    if [ -n "${XENGUEST_IMAGE_KERNEL}" ]; then
        call_xenguest_mkimage partial \
            --xen-kernel=${DEPLOY_DIR_IMAGE}/${XENGUEST_IMAGE_KERNEL}
    fi

    # Pack and deploy the final image
    rm -f ${DEPLOYDIR}/${XENGUEST_IMAGE_NODISK_DEPLOY}
    call_xenguest_mkimage pack ${DEPLOYDIR}/${XENGUEST_IMAGE_NODISK_DEPLOY}
}
do_deploy[depends] += "virtual/kernel:do_deploy"
do_deploy[depends] += "xenguest-base-image:do_deploy"

addtask deploy before do_build after do_install

