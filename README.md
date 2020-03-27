Introduction
------------
This repository contains Arm layers for OpenEmbedded

meta-arm:
	This layer provides support for general recipes for the Arm
	architecture.  Anything that's not needed explicitly for BSPs, the IOTA
	distribution, or destined to be upstreamed belongs here.

meta-arm-bsp:
	This layer provides support for Arm reference platforms

meta-arm-iota:
	This layer provides support for Arm's IOTA Linux Distribution

meta-arm-toolchain:
	This layer provides support for Arm's GNU-A toolset releases

meta-arm-autonomy:
    This layer provides a reference stack for autonomous systems.

Contributing
------------
Currently, we only accept patches from the meta-arm mailing list.  For general
information on how to submit a patch, please read
https://www.openembedded.org/wiki/How_to_submit_a_patch_to_OpenEmbedded

E-mail meta-arm@lists.yoctoproject.org with patches created using this process

Reporting bugs
--------------
E-mail meta-arm@lists.yoctoproject.org with the error encountered and the steps
to reproduce the issue


Maintainer(s)
-------------
* Jon Mason <jon.mason@arm.com>
