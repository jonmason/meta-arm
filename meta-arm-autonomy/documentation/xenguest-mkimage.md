Xenguest mkimage
================

Introduction
------------

xenguest-mkimage is a tool to create and modify images to be used as Guest with
Xen. It defines a format to store completely defined guests as a file or as
a directory and provides options to create and modify those images.

A xenguest image contains all elements required to create a xen guest.
This is the base elements like a Xen configuration and a Linux kernel binary
but also some more advanced elements like init scripts or a disk definition.

The format is made to be deployable easily by storing everything in a single
file and provide tools to easily manipulate the images. It can also easily be
extended to have features like encryption or signature of images, updates or
complex configurations by providing features to have init script that will be
executed on the host embedded inside the image.

Xenguest images content
-----------------------

### params.cfg

This file contains parameters that can be used by tools to configure some
functionalities on the host. This can be used by init scripts to have
configurable parameters as it is sourced before calling init scripts.

### guest.cfg and guest.d

guest.cfg is the main xen configuration and guest.d contains optional
configuration parts. All those will be merged into one final xen configuration
before starting the guest.

### files
This directory contains files that can be used by the xen configuration, for
example the binary of the kernel referenced in xen configuration).
This is where the kernel binary, the dtb or a ramdisk will be stored.

### init.pre, init.d and init.post
These directories contain init scripts that will be executed on the host
during the guest startup. Those must be shell scripts and each directory
contains scripts called at a different time:
 - init.pre: scripts executed before the guest is created. This can be used
     to prepare some features required to create the guest in xen or to
     generate part of the xen configuration dynamically.
 - init.d: scripts executed when the guest has been created but before it is
     started. This can be used to do some xenstore operations or configure the
     guest behaviour using xl, for example.
 - init.post: scripts executed just after starting the guest. This can be
     used to configure things created by xen for the guest like network
     network interfaces.

When a directory contains several scripts, those will be called in alphabetical
order.

### disk.cfg and disk-files
disk.cfg contains the guest disk description (disk size and disk partitions).
The file contains the following entries:
- `DISK_SIZE=X`: size of the disk to create in GB
- `DISK_PARTX=SIZE:FS:CONTENT`: create a partition number X (1 to 4) with a
  size of SIZE GB, format it with filesystem FS (can be ext2, ext3, ext4, vfat
  or swap) and extract CONTENT as initial partition content
  (.tar[.gz|.xz|.bz2] file or img[.gz|.bz2] file to be dumped in the partition). FS and
  CONTENT can be empty.

The disk-files contain files to be used for initializing the disk partitions
content. Those should be used to create a LVM or a physical disk and initialize
it (create partitions, format them and put the initial content).

Usage
-----

xenguest-mkimage is a shell script which must be called like this:
`xenguest-mkimage OPERATION XENGUEST [OPTIONS]`

### Operations
- create: create a xenguest image. If XENGUEST is an existing empty directory,
  the image is created as a directory otherwise it will be created as a file.
- check: verify that XENGUEST is a valid xenguest image.
- update: modify a xenguest image (see --help for a list of operations).
- pack: pack a xenguest image directory into a xenguest image file. The file to
  be created must be given as 3rd argument.
- extract: extract a xenguest image file into a directory. The destination
  directory must be given as 3rd argument.
- dump-xenconfig: dump xenguest image xen configuration.
- dump-diskconfig: dump xenguest image disk configuration.
- dump-paramsconfig: dump xenguest image parameters configuration.

For a detailed help on available operations, please use:
`xenguest-mkimage --help`

### Options
- --kernel=FILE: add kernel FILE as guest kernel. This is both adding the file
  to the image and modifying the xen configuration to use it.
- --xen-memory=SIZE: set the guest memory size in MB.
- --xen-extra: add a kernel command line argument. This can be called several
  times to add several command line options.
- --xen-device-tree=FILE: add dtb FILE as device tree. This both adding the
  file to the image and modifying the xen configuration to use it.
- --init-script=FILE: add guest init script. The script is embedded inside the
  image file. Several script can be added and the basename of FILE is used to
  distinguish them (calling the option twice with the same file will update the
  script in the image with the second one).
 --disk-size=SIZE: set the guest disk size to SIZE in GB. Calling this with 0
  disable the guest disk.
- --disk-add-part=NUM:SIZE:FS:CONTENT: This is adding a partition to the
  xenguest image disk. The partition is described with the arguments:
  - NUM: partition number.
  - SIZE: partition size in GB.
  - FS: filesystem to format the partition with. This can be ext2, ext3, ext4,
    vfat of swap. If empty the partition is not formated.
  - CONTENT: tar of img file to use to initialize the partition. The file must
    be added to the image using --disk-add-file=FILE:CONTENT.

For a detailed help on available options, please use:
`xenguest-mkimage OPERATION --help`

