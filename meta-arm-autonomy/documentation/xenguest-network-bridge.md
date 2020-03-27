xenguest network bridge
=======================

Introduction
------------

xenguest-network-bridge is creating a network bridge to allow some guests to
have a direct connection to the external network.
To do this, a bridge is created on the host using brctl with the network
interfaces added to it so that the bridge is connected to the external network.
It is also adding a guest init script which will, for guests configured to use
it, create a virtual network interface for the guest and connect it to the
network bridge on the host.

Usage
-----

On the host the package xenguest-network-bridge must be included in your image.

On the xenguest image of your guest, the parameter NETWORK_BRIDGE must be set
to 1 (using xenguest-mkimage --set-param=NETWORK_BRIDGE=1).

Bitbake parameters
------------------
Several parameters are available to configure the xenguest network bridge
during Yocto project compilation (those can be set in your project local.conf,
for example).

The following parameters are available:

- XENGUEST_NETWORK_BRIDGE_NAME: This variable defines the name of the network
  bridge that is created on the host during init.
  This is set by default to "xenbr0".

- XENGUEST_NETWORK_BRIDGE_MEMBERS: This variable defines the list of network
  interfaces that are added to the bridge when it is created on the host during
  init.
  This is set by default to "eth0".

- XENGUEST_NETWORK_BRIDGE_CONFIG: This variable defines the configuration file
  to use to configure the bridge network. By default it points to have file
  configuring the network using dhcp.
  You can provide a different file using a bbappend and make this variable
  point to it if you want to customize your network configuration.

- XENGUEST_IMAGE_NETWORK_BRIDGE: This variable can be set to 0 or 1 on guest
  projects to enable or not the connection of the guest to the host bridge.
  This is set by default to "1".

