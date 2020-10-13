# Extra machine settings for juno

# Juno board has 2 network interfaces, add both of them to the bridge
XENGUEST_NETWORK_BRIDGE_MEMBERS ?= "eth0 eth1"
