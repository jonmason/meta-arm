GRUB_BUILDIN += "${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'xen_boot', '', d)}"
