# Use OVERRIDES to minimize the usage of
# ${@bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', ...
OVERRIDES:append = "${ARM_AUTONOMY_HOST_OVERRIDES}"

# Make Xen machine specific
# This ensures that sstate is properly handled and that each machine can have
# its own configuration
PACKAGE_ARCH:autonomy-host = "${MACHINE_ARCH}"

PACKAGECONFIG:remove:autonomy-host = "sdl"
