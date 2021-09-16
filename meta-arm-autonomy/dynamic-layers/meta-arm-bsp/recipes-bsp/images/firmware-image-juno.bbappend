# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'autonomy-host', ...
OVERRIDES:append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

FILESEXTRAPATHS:prepend:autonomy-host := "${THISDIR}/${PN}:"

DEPENDS:append:autonomy-host = " dos2unix-native"

SRC_URI:append:autonomy-host = " file://add-xen-support.patch;patchdir=../"

do_install:append:autonomy-host() {
    mv -v ${D}/${UNPACK_DIR}/SOFTWARE/uEnv.txt \
          ${D}/${UNPACK_DIR}/SOFTWARE/uenvfile
    for dir in $(ls ${D}/${UNPACK_DIR}/SITE1/)
    do
        unix2dos ${D}/${UNPACK_DIR}/SITE1/${dir}/images.txt
    done
}

DEPLOY_EXTRA_DEPS ??= ""
DEPLOY_EXTRA_DEPS:autonomy-host = "xen:do_deploy xen-devicetree:do_deploy"

do_deploy[depends] += "${DEPLOY_EXTRA_DEPS}"

do_deploy:prepend:autonomy-host() {
    # To avoid dependency loop between firmware-image-juno:do_install,
    # xen:do_deploy and xen-devicetree:do_deploy when
    # INITRAMFS_IMAGE_BUNDLE = "1", we need to handle the xen and
    # xen-devicetree binaries copying in the do_deploy task.

    mkdir -p ${D}/${UNPACK_DIR}/SOFTWARE/XEN
    cp  -v ${DEPLOY_DIR_IMAGE}/xen-${COMPATIBLE_MACHINE}.efi \
        ${D}/${UNPACK_DIR}/SOFTWARE/XEN/xen

    for dtb in $(basename -s .dtb ${KERNEL_DEVICETREE})
    do
        cp -v ${DEPLOY_DIR_IMAGE}/${dtb}-xen.dtb \
            ${D}/${UNPACK_DIR}/SOFTWARE/XEN/${dtb}.dtb
    done

    bbnote "Xen binaries added under SOFTWARE/XEN directory"

    if [ "${INITRAMFS_IMAGE_BUNDLE}" != "1" -a "${KERNEL_ALT_IMAGETYPE}" = "Image.lzma" ]; then
        # KERNEL_ALT_IMAGETYPE is expected to be Image.lzma,
        # however NOR flash filesystem is DOS compatible with 8.3 naming,
        # so we need to replace ".lzma" with ".lzm"
        cp -L -f ${DEPLOY_DIR_IMAGE}/${KERNEL_ALT_IMAGETYPE} \
                 ${D}/${UNPACK_DIR}/SOFTWARE/Image.lzm
    fi
}
