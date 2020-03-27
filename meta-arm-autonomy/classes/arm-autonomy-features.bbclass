# Include arm-autonomy distro config files if the distro features are set

require ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', '${ARM_AUTONOMY_DISTRO_CFGDIR}/arm-autonomy-host.inc', '', d)}
require ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-guest', '${ARM_AUTONOMY_DISTRO_CFGDIR}/arm-autonomy-guest.inc', '', d)}

