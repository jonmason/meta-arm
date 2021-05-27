PACKAGECONFIG_remove = "\
    ${@bb.utils.contains('DISTRO_FEATURES', \
                         'arm-autonomy-host', \
                         'sdl', '', d)}"
