arm-autonomy Quick Start
==================

This documentation is explaining how to quickly start with arm-autonomy layer
and the main features provided.
You will find in the documentation directory some more detailed documentation
for each of the functionalites provided by this layer.

What to use this layer for?
---------------------------
Using this layer, you can easily and rapidly create a system based on Xen with
one or more guests created using Yocto.

For this you will need to create at least 2 Yocto projects:
- a host project: This one will compile Xen and create a Linux system to be
  used as Xen Dom0. The Linux system will contain all functionalities required
  to start and manage guests.
- one or several guest projects: Those will create Linux systems with the
  required Linux kernel configuration to run as Xen DomU.

Prepare your system
-------------------

First you must download the Yocto layers needed:
 - [meta-openembedded](https://git.openembedded.org/meta-openembedded)
 - [poky](https://git.yoctoproject.org/poky)
 - [meta-virtualization](https://git.yoctoproject.org/meta-virtualization)
 - [meta-arm](https://git.yoctoproject.org/meta-arm)
 - all other layers you might want to use

For each of the downloaded layer make sure you checkout the release of Yocto
you want to use (for example zeus using `git checkout zeus`).

Please follow [Yocto documentation](https://www.yoctoproject.org/docs/latest/brief-yoctoprojectqs/brief-yoctoprojectqs.html)
in order to have the required dependencies.


Create a project
----------------

Here are the main steps to create an arm-autonomy project:

1. create a new Yocto project using `oe-init-build-env` in a new directory:
  ```
  oe-init-build-env my-project
  ```

2. Add `meta-arm/meta-arm-autonomy` layer to the list of layers of your
  project in the `conf/bblayers.conf`. Also add any other layers you
  might need (for example `meta-arm/meta-arm-bsp` and `meta-arm/meta-arm` to
  use Arm boards like Juno or FVP emulator). You can achieve this by using
  the `bitbake-layers add-layer layerdir [layerdir ...]` command.
  For example:
  ```
  export LAYERDIR_BASE="/home/user/arm-autonomy/"
  bitbake-layers add-layer $LAYERDIR_BASE/meta-poky $LAYERDIR_BASE/meta-yocto-bsp \
   $LAYERDIR_BASE/meta-openembedded/meta-oe $LAYERDIR_BASE/meta-openembedded/meta-python \
   $LAYERDIR_BASE/meta-openembedded/meta-filesystems $LAYERDIR_BASE/meta-openembedded/meta-networking \
   $LAYERDIR_BASE/meta-virtualization $LAYERDIR_BASE/meta-arm/meta-arm-autonomy \
   $LAYERDIR_BASE/meta-arm/meta-arm $LAYERDIR_BASE/meta-arm/meta-arm-bsp
  ```

  Example of a `conf/bblayers.conf`:
  ```
  BBLAYERS ?= " \
    /home/user/arm-autonomy/poky/meta \
    /home/user/arm-autonomy/poky/meta-poky \
    /home/user/arm-autonomy/poky/meta-yocto-bsp \
    /home/user/arm-autonomy/meta-openembedded/meta-oe \
    /home/user/arm-autonomy/meta-openembedded/meta-python \
    /home/user/arm-autonomy/meta-openembedded/meta-filesystems \
    /home/user/arm-autonomy/meta-openembedded/meta-networking \
    /home/user/arm-autonomy/meta-virtualization \
    /home/user/arm-autonomy/meta-arm/meta-arm-autonomy \
    /home/user/arm-autonomy/meta-arm/meta-arm \
    /home/user/arm-autonomy/meta-arm/meta-arm-bsp \
    "
  ```

Those steps will have to be done for each project you will have to create.

Host project
------------
The host project will build Xen and the Dom0 Linux. It will be the only project
that will be specific to the board (MACHINE) you will be running on.

To create a host project:
1. Follow the steps of "Create a project"

2. Add the layers in `bblayers.conf` required to build a Yocto project for the
   board you want to use.
   For example to use Arm FVP Base emulator, add `meta-arm/meta-arm` and
   `meta-arm/meta-arm-bsp`.

3. edit conf/local.conf to add `arm-autonomy-host` to the DISTRO_FEATURES and
   set MACHINE to the board you want to use.
   For example, add the following lines:
  ```
  MACHINE = "fvp-base"
  DISTRO_FEATURES += "arm-autonomy-host"
  ```

4. build the image using `bitbake arm-autonomy-host-image-minimal`

The project will generate a Linux kernel, a root filesystem, a Xen binary and
a DTB modified to include the required entries to boot Xen and Linux as Dom0
(this DTB has the extension `-xen.dtb`).

To boot the system using an u-boot base board you will need to:
- Load the kernel (by default at 0x80080000 unless you modify
  XEN_DEVICETREE_DOM0_ADDR value)
- Load the xen device tree (for example at 0x83000000)
- Load the xen-efi binary (for example at 0x84000000)
- run using `booti 0x84000000 - 0x83000000`

In this example the addresses might need to be adapted depending on your board.

For arm-autonomy host on FVP-Base u-boot has been modified such that
`booti 0x84000000 - 0x83000000` is the default boot command. If FVP-Base is your
MACHINE target there should be no need to interfere with u-boot.

Guest project
-------------
The guest projects are not target specific and will use a Yocto MACHINE defined
in meta-arm-autonomy to include only the Linux configuration required to run
a xen guest.

To create a guest project:

1. Follow the steps of "Create a project"

2. Optionaly add layers required to build the image and features you need.

3. edit conf/local.conf to add `arm-autonomy-guest` to the DISTRO_FEATURES and
   set MACHINE to `arm64-autonomy-guest`:
  ```
  MACHINE = "arm64-autonomy-guest"
  DISTRO_FEATURES += "arm-autonomy-guest"
  ```

4. build the image you want.
   For example `bitbake core-image-minimal`

The build will create a ".xenguest" image that can be use on an host project
with the xenguest-manager.

Include guests directly in the host image
-----------------------------------------
The layer provides a way to directly include in the host project one or several
images generated by guest projects.

To use this feature, you must edit your host project `local.conf` file and
add set ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS to the list of xenguest images
you want to include in your host. Each xenguest image must be given using a
full path to it.
For example:
```
ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS = "/home/user/guest-project/tmp/deploy/images/arm64-autonomy-guest/core-image-minimal-arm64-autonomy-guest.xenguest;guestname=myguest"
```
This will add the guest and name it `myguest` on the host project image and
the xenguest-manager will automatically boot it during startup.

Add support for your board
--------------------------
Most of arm-autonomy layer is board independent but some functionalities
might need to be customized for your board:

### Add the kernel configuration for the host
The layer is using KERNEL_FEATURES to add drivers required to be a Xen Dom0
system.
Depending on the kernel used by your BSP and how it is configured you might
need to add the required drivers to your kernel configuration:
- if KERNEL_FEATURES system is supported by your kernel, make sure that the
file `recipes-kernel/linux/linux-arm-autonomy.inc` from the layer is included
by your kernel recipe.
- if it is not supported, you must add the proper drivers inside your kernel
(modules are possible but they must be loaded before xenguest-manager is
started). You can find the complete list of the kernel configuration elements
required in `recipes-kernel/linux/arm-autonomy-kmeta/features/arm-autonomy/xen-host.cfg`.

### Define the drive and partition to use for the LVM volume
The xenguest-manager is creating disk hard drive using LVM on an empty
partition. The default value is set to use /dev/sda2.
You can change this for your board by setting XENGUEST_MANAGER_VOLUME_DEVICE.

Check `recipes-extended/xenguest/xenguest-manager.bbappend` for examples.

Please also read xenguest-manager.md.

### Define the interface to add to xenguest network bridge
xenguest-network bridge is creating a bridge on the host and adds network
interfaces to it so that guest connected to it have access to external network.
By default `eth0` is set as the list of interfaces to be added to the bridge.
Depending on your board or use case you might want to use an other interface
or use multiple interfaces.
You can change this for your board by setting XENGUEST_NETWORK_BRIDGE_MEMBERS.

Check `recipes-extended/xenguest/xenguest-network-bridge.bbappend` for
exmaples.

Please also read xenguest-network-bridge.md.

### Define the network configuration of the xenguest network bridge
xenguest network bridge is putting the host network interfaces in a bridge
and is configuring it by default to use dhcp.
If you need a different type of configuration you can set
XENGUEST_NETWORK_BRIDGE_CONFIG in a xenguest-network-bridge.bbappend to use
a different file.
The recipe will look for the file in ${WORKDIR} so you will need to add it to 
SRC_URI in your bbappend.
The recipe will also substitute `###BRIDGE_NAME###` with the bridge name
configured in ${XENGUEST_NETWORK_BRIDGE_NAME}.

You can find an example configuration file in
`recipes-extended/xenguest/files/xenguest-network-bridge-dhcp.cfg.in`.

Please also read xenguest-network-bridge.md.

### Customize Dom0 and Xen boot arguments for you board
xen-devicetree is writting inside the generated DTB Xen and Linux boot
arguments as long as the address where Dom0 Linux kernel can be found.
You might need to have different values for your board or depending on your
use case.

You can find examples to customize this in
`recipes-extended/xen-devicetree/xen-devicetree.bbappend`.

Please also read xen-devicetree.md.

