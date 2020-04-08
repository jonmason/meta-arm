FILESEXTRAPATHS_prepend_juno := "${@bb.utils.contains('DISTRO_FEATURES', 'xen', '${THISDIR}/files/juno:', '', d)}"

JUNO_EXTRA_DEPS_append = "${@bb.utils.contains('DISTRO_FEATURES', 'xen', ' xen:do_deploy', '', d)}"

do_deploy_append_juno() {

    if [ "${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'yes', 'no', d)}" = "yes" ]; then
        cp -a \
            ${DEPLOY_DIR_IMAGE}/xen-${COMPATIBLE_MACHINE}.efi \
            ${WORKDIR}/juno-oe-uboot/SOFTWARE/xen
    fi

}
