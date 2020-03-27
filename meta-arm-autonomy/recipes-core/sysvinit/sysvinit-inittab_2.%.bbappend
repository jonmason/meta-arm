# if arm-autonomy-guest is activated, we are running as a xen guest so we must
# have a console on hvc0
# This is normally done in meta-virtualization if xen is activated but here
# we don't have xen activated.
#

SYSVINIT_ADDHVC0 = "${@bb.utils.contains('DISTRO_FEATURES', \
    'arm-autonomy-guest', 'true', 'false', d)}"

do_install_append() {
    if ${SYSVINIT_ADDHVC0}; then
        echo "" >> ${D}${sysconfdir}/inittab
        echo "X0:12345:respawn:/sbin/getty 115200 hvc0" >> \
            ${D}${sysconfdir}/inittab
    fi
}
