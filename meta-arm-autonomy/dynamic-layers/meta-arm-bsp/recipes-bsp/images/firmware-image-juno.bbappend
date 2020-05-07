# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'xen', ...
OVERRIDES_append = "${@bb.utils.contains('DISTRO_FEATURES', 'xen', ':xen', '', d)}"

FILESEXTRAPATHS_prepend_xen := "${THISDIR}/${PN}:"

DEPLOY_EXTRA_DEPS ??= ""
DEPLOY_EXTRA_DEPS_xen = "xen:do_deploy xen-devicetree:do_deploy"

do_deploy[depends] += "${DEPLOY_EXTRA_DEPS}"

do_deploy_prepend_xen() {
    # To avoid dependency loop between firmware-image-juno:do_install,
    # xen:do_deploy and xen-devicetree:do_deploy when
    # INITRAMFS_IMAGE_BUNDLE = "1", we need to handle the xen and
    # xen-devicetree binaries copying in the do_deploy task.
    cp  ${DEPLOY_DIR_IMAGE}/xen-${COMPATIBLE_MACHINE}.efi \
        ${D}/${UNPACK_DIR}/SOFTWARE/xen
    cp ${DEPLOY_DIR_IMAGE}/*xen.dtb \
        ${D}/${UNPACK_DIR}/SOFTWARE/
}
