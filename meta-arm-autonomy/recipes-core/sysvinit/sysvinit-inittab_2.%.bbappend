# if arm-autonomy-host or arm-autonomy-guest are activated, we need to install
# the getty-wrapper to spawn the login console on /dev/hvc0.
# This is normally done in meta-virtualization if virtualization and xen
# DISTRO_FEATURES are activated.

# In both arm-autonomy-host and arm-autonomy-guest we don't have virtualization
# in DISTRO_FEATURE. Hence, manually include sysvinit-inittab_virtualization.inc
# to install the getty-wrapper.
require ${@bb.utils.contains_any('DISTRO_FEATURES', \
                                 'arm-autonomy-host arm-autonomy-guest', \
                                 'recipes-core/sysvinit/sysvinit-inittab_virtualization.inc', \
                                 '', d)}

# For arm-autonomy-guest we don't have xen in DISTRO_FEATURES. Hence, manually
# include sysvinit-inittab_xen.inc to append the getty-wrapper entry to
# /etc/inittab.
require ${@bb.utils.contains('DISTRO_FEATURES', \
                             'arm-autonomy-guest', \
                             'recipes-core/sysvinit/sysvinit-inittab_xen.inc', \
                             '', d)}
