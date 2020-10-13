# Board specific configuration for the manager

# FVP uses vda as hard drive and partition 2 is the
# default rootfs, so use vda3 for guest lvm
XENGUEST_MANAGER_VOLUME_DEVICE_fvp-base ?= "/dev/vda3"
