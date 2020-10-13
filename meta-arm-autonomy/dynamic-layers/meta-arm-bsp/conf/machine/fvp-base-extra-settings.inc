# Extra machine settings for fvp-base

# FVP uses vda as hard drive and partition 2 is the
# default rootfs, so use vda3 for guest lvm
XENGUEST_MANAGER_VOLUME_DEVICE ?= "/dev/vda3"

XENGUEST_NETWORK_BRIDGE_MEMBERS ?= "eth0"
