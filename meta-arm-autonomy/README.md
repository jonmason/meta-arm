meta-arm-autonomy Yocto Layer
=============================

Introduction
------------
This layer provides an hypervisor based solution (currently based on Xen) for
autonomous system. It contains recipes and classes to build host and guests
systems.

Dependencies
------------
This layer depends on several other Yocto layers:
* meta-openembedded (https://git.openembedded.org/meta-openembedded)
* poky (https://git.yoctoproject.org/poky)
* meta-virtualization (https://git.yoctoproject.org/meta-virtualization)

Distribution Features
---------------------
This layer is adding the following Yocto DISTRO_FEATURES:

* arm-autonomy-host: this feature activates functionalities required to build
  an autonomy host system. It is doing the following:
  - add 'xen' and 'ipv4' to DISTRO_FEATURES.
  - add xen backend drivers to linux kernel configuration.

Bitbake variables
-----------------
Some recipes and classes in this layer are introducing variables which can be
modified by the user in local.conf.
Each recipe introducing such variables has a chapter "Bitbake parameters" in
its documentation.

Those documentation files should be checked for variables:

BSPs
----
This layer is adding the following machines:

Images
------
This layer is adding the following images:

* arm-autonomy-host-image-minimal: this image includes all elements required
  to create a minimal arm-autonomy-host system. This includes xen and tools to
  manage xen guests. This image depends on 'arm-autonomy-host' distribution
  feature.

Recipes and classes
-------------------
This layer is adding the following recipes and classes:

Contributing
------------
This project has not put in place a process for contributions currently. If you
would like to contribute, please contact the maintainers


Maintainer(s)
-------------
* Bertrand Marquis <bertrand.marquis@arm.com>
* Filipe Rinaldi <filipe.rinaldi@arm.com>
