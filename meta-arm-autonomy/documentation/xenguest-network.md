Xenguest Network
================

Introduction
------------

The xenguest-network package is primarly creating a network bridge to share
the host eth physical interfaces with the guests virtual interfaces (vif).
This way the guests can have access to the external network.

At the moment 3 types of network arrangements are provided:

- Bridge: where the guest vif is added to the created bridge interface;

- NAT: where a private subnet is created for the guest,
  a kea dhcp4 server is started on the host to serve the guest
  and the proper iptables rules are created
  to allow the guest to access the external network;

- None: the guest vif is not connected to the bridge.

Usage
-----

On the host project the package xenguest-network must be included in your
image, and on the guest project the XENGUEST_NETWORK_TYPE needs to be set to
"bridge", "nat" or "none".

Bitbake parameters
------------------

Several parameters are available to configure the xenguest network bridge
during Yocto project compilation (those can be set in your project local.conf
or xenguest-network.bbappend, for example).

The following parameters are available:

- XENGUEST_NETWORK_BRIDGE_NAME: This variable defines the name of the network
  bridge that is created on the host during init.
  This is set by default to "xenbr0".

- XENGUEST_NETWORK_BRIDGE_MEMBERS: This variable defines the list of the
  physical network interfaces that are added to the bridge when it is created
  on the host during init.
  By default no physical interfaces are added.

- XENGUEST_NETWORK_BRIDGE_CONFIG: This variable defines the configuration file
  to use to configure the bridge network. By default it points to have file
  configuring the network using dhcp.
  You can provide a different file using a bbappend and make this variable
  point to it if you want to customize your network configuration.

- XENGUEST_IMAGE_NETWORK_TYPE: This variable can be set to "bridge" (default),
  "nat" or "none".
  The **bridge** type will add the domU vif interface to a bridge which also
  contains the dom0 physical interface giving the guest direct access to the
  external network.
  The **nat** type will setup a private network between dom0 and domU, setup
  the appropriate routing table, configure and run the kea dhcp4 server
  on dom0 to serve the domU and apply the iptables rules to allow the guest
  to acess the external network. The kea dhcp4 server configuration for
  the guest can be customised by replacing the
  "meta-arm-autonomy/recipes-extended/xenguest/files/kea-subnet4.json" file
  in a xenguest-network.bbappend. The kea-subnet4.json file is installed in
  the xenguest image and copied to
  "/etc/xenguest/guests/${guestname}/files/kea-subnet4.json" when the guest
  image is created. It will be consumed by the
  "/etc/xen/scripts/vif-post.d/00-vif-xenguest.hook" script which is called by
  "/etc/xen/scripts/vif-nat" script when starting/stopping the xenguest.
  After guest start, "/etc/xenguest/init.post/xenguest-network-init-post.sh"
  script is called to reload kea dhcp4 server with updated configuration,
  after virtual network interface is ready.
  In the guest project, the NAT port forward can be customised by changing
  the XENGUEST_IMAGE_HOST_PORT (default: "1000 + ${domid}") and
  XENGUEST_IMAGE_GUEST_PORT (default: "22") variables in local.conf or
  xenguest-base-image.bbappend. This configuration is implemented and installed
  in "/etc/xenguest/guests/${guestname}/files/00-xenguest-nat-port-forward.hook"
  script which is called by "/etc/xen/scripts/vif-post.d/00-vif-xenguest.hook".
  The **none** type will not affect any networking setting between on dom0 and
  domU.
