# Make Xen machine specific
# This ensures that sstate is properly handled and that each machine can have
# its own configuration
PACKAGE_ARCH = "${MACHINE_ARCH}"

PACKAGECONFIG_remove = "\
    ${@bb.utils.contains('DISTRO_FEATURES', \
                         'arm-autonomy-host', \
                         'sdl', '', d)}"
