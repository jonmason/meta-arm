# Add arm-autonomy kernel support
require ${@bb.utils.contains_any('DISTRO_FEATURES', \
                                 'arm-autonomy-host arm-autonomy-guest', \
                                 'linux-arm-autonomy.inc', \
                                 '', d)}
