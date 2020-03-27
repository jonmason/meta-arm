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

2. edit the file `conf/bblayers.conf` and add `meta-arm/meta-arm-autonomy`
  layer to the list of layers of your project. Also add any other layers you
  might need (for example `meta-arm/meta-arm-bsp` and `meta-arm/meta-arm` to
  use Arm boards like Juno or FVP emulator).
  For example:
  ```
  BBLAYERS ?= " \
    /home/user/arm-autonomy/poky/meta \
    /home/user/arm-autonomy/poky/meta-poky \
    /home/user/arm-autonomy/poky/meta-yocto-bsp \
    /home/user/arm-autonomy/meta-openembedded/meta-oe \
    /home/user/arm-autonomy/meta-openembedded/meta-python \
    /home/user/arm-autonomy/meta-openembedded/meta-filesystems \
    /home/user/arm-autonomy/meta-openembedded/meta-networking \
    /home/user/arm-autonomy/meta-arm/meta-arm \
    /home/user/arm-autonomy/meta-arm/meta-arm-bsp \
    /home/user/arm-autonomy/meta-virtualization \
    /home/user/arm-autonomy/meta-arm/meta-arm-autonomy \
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


