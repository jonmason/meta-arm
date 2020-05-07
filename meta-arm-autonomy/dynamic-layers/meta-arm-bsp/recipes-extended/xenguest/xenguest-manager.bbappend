# Board specific configuration for the manager

# FVP and Foundation are using vda as hard drive and partition 2 is the
# default rootfs, so use vda3 for guest lvm
XENGUEST_MANAGER_VOLUME_DEVICE_foundation-armv8 ?= "/dev/vda3"
XENGUEST_MANAGER_VOLUME_DEVICE_fvp-base ?= "/dev/vda3"
