FILESEXTRAPATHS_prepend_juno := "${@bb.utils.contains('DISTRO_FEATURES', 'xen', '${THISDIR}/${PN}:', '', d)}"

INSTALL_EXTRA_DEPS_juno = "${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'xen:do_deploy', '', d)}"

do_install[depends] += "${INSTALL_EXTRA_DEPS}"

do_install_append_juno() {
    if [ "${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'yes', 'no', d)}" = "yes" ]; then
        cp  ${DEPLOY_DIR_IMAGE}/xen-${COMPATIBLE_MACHINE}.efi \
            ${D}/${UNPACK_DIR}/SOFTWARE/xen
        cp ${DEPLOY_DIR_IMAGE}/*xen.dtb \
            ${D}/${UNPACK_DIR}/SOFTWARE/
    fi
}
