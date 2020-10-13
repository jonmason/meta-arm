XENGUEST_NETWORK_BRIDGE_MEMBERS_n1sdp ?= "eth0"

XENGUEST_NETWORK_BRIDGE_MEMBERS_fvp-base ?= "eth0"

# Juno board has 2 network interfaces, add both of them to the bridge
XENGUEST_NETWORK_BRIDGE_MEMBERS_juno ?= "eth0 eth1"
