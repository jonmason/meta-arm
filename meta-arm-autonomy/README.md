meta-arm-autonomy Yocto Layer
=============================

Introduction
------------
This layer provides an hypervisor based solution (currently based on Xen) for
autonomous system. It contains recipes and classes to build host and guest
images.

To start using this layer, please check the
[Quick Start Guide](documentation/arm-autonomy-quickstart.md).

Dependencies
------------
This layer depends on several other Yocto layers:
* meta-openembedded (https://git.openembedded.org/meta-openembedded)
* poky (https://git.yoctoproject.org/poky)
* meta-virtualization (https://git.yoctoproject.org/meta-virtualization)
* meta-networking (git://git.openembedded.org/meta-openembedded)

Distribution Features
---------------------
This layer adds the following Yocto DISTRO_FEATURES:

* arm-autonomy-host: this feature activates functionalities required to build
  an autonomy host system. It has the following effects:
  - add 'xen' and 'ipv4' to DISTRO_FEATURES.
  - add xen backend drivers to linux kernel configuration.
  - To reduce the root filesystem image size the kernel image is not installed.

* arm-autonomy-guest: this feature activates functionalities to run as guest
  of an autonomy system. It is doing the following:
  - add 'ipv4' to DISTRO_FEATURES.
  - add xen frontend drivers to linux kernel configuration.
  - add console on hvc0 during init.

Bitbake variables
-----------------
Some recipes and classes in this layer are introducing variables which can be
modified by the user in local.conf.
Each recipe introducing such variables has a chapter "Bitbake parameters" in
its documentation.

Those documentation files should be checked for variables:
- [xen-devicetree](documentation/xen-devicetree.md)
- [xenguest-manager](documentation/xenguest-manager.md)
- [xenguest-network](documentation/xenguest-network.md)

BSPs
----
This layer adds the following machine:

* arm64-autonomy-guest: This machine creates a minimal BSP suitable to be used
  as an autonomy guest. It is in fact only activating ARM64 architecture and
  SMP in the linux kernel and is enabling the DISTRO_FEATURE
  'arm-autonomy-guest'.

Images
------
This layer is adding the following images:

* arm-autonomy-host-image-minimal: This image includes all elements required
  to create a minimal arm-autonomy-host system. This includes xen, and tools to
  manage xen guests and xenguest images. This image depends on
 'arm-autonomy-host' distribution feature.

Recipes and classes
-------------------
This layer adds the following recipes and classes:

* [xen-devicetree](documentation/xen-devicetree.md): This is a recipe to modify
  a device tree blob to add information required to boot xen and a Dom0 linux.

* [xenguest-mkimage](documentation/xenguest-mkimage.md): This is a tool used to
  create and modify images to be used as Xen guests.

* [xenguest-manager](documentation/xenguest-manager.md): This is a tool used to
  create/remove/start/stop xen guest generated using xenguest-mkimage.

* [xenguest-network](documentation/xenguest-network.md): This
  recipe add tools and init scripts to create a bridge connected to the
  external network on the host and allow guests to be connected to it.

Contributing
------------
This project has not put in place a process for contributions currently. If you
would like to contribute, please contact the maintainers


Maintainer(s)
-------------
* Diego Sueiro <diego.sueiro@arm.com>
* Bertrand Marquis <bertrand.marquis@arm.com>
