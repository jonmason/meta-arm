require ${@bb.utils.contains('DISTRO_FEATURES', \
                             'arm-autonomy-host', \
                             'qemu-autonomy-host.inc', '', d)}
