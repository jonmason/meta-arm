GRUB_BUILDIN += "${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', 'xen_boot', '', d)}"
