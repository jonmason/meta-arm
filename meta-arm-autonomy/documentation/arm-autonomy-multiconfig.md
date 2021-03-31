arm-autonomy Multiconfig Build Environment Instructions
==================

This documentation explains how to simplify the process of building hosts
and guests in a single bitbake command, rather than in seperate build
folders. You can read more about multiconfig in the bitbake documentation:

 - [bitbake user manual](https://www.yoctoproject.org/docs/latest/bitbake-user-manual/bitbake-user-manual.html)

To achieve a multiconfig build, a number of different config files need to
be created in a single build directory.

Create a new project
----------------

Before you start, you will need to follow the instructions in
"Create a project" from the quickstart guide, to create a new project
directory with
  ```
  oe-init-build-env my-mc-project
  ```
Ensure it has all the required layers in bblayers.conf as listed in
`arm-autonomy-quickstart.md`. The result should be a directory containing:

```
-- conf
 | -- bblayers.conf
 | -- local.conf
 | -- templateconf.cfg
```

Add multiconfig
----------------

The steps required to make the project build both the host and any
number of guests as required are:

1. Create a new directory under `conf/` named `multiconfig/`

2. Create two new files in this directory:
`multiconfig/host.conf`
`multiconfig/guest.conf`
These files will contain any configurations that are specific to either the
host or the guest. The resulting directory tree should be:

```
-- conf
 | -- bblayers.conf
 | -- local.conf
 | -- templateconf.cfg
 | -- multiconfig
    | -- host.conf
    | -- guest.conf
```

3. In `local.conf` the following config variables must be added:

```
MACHINE ?= "fvp-base"

# ---Guest Config Start--- #
MC_GUEST = "guest"

MC_GUEST_NAME = "guest1"

MC_GUEST_IMAGERECIPE = "core-image-minimal"
MC_GUEST_MACHINE = "arm64-autonomy-guest"

MC_GUEST_INITRAMFS_IMAGE_BUNDLE ?= ""
MC_GUEST_INITRAMFS_IMAGE ?= ""

# Uncomment for initramfs
#MC_GUEST_INITRAMFS_IMAGE_BUNDLE = "1"
#MC_GUEST_INITRAMFS_IMAGE = "${MC_GUEST_IMAGERECIPE}"

# These variables are set automatically, don't override them!
MC_GUEST_FILENAME_PREFIX = "${@ 'Image-initramfs' if d.getVar('MC_GUEST_INITRAMFS_IMAGE_BUNDLE',d) else '${MC_GUEST_IMAGERECIPE}' }"

MC_GUEST_FILENAME = "${MC_GUEST_FILENAME_PREFIX}-${MC_GUEST_MACHINE}.xenguest"

MC_GUEST_DEP = "${@ 'virtual/kernel:do_deploy' if d.getVar('MC_GUEST_INITRAMFS_IMAGE_BUNDLE',d) else '${MC_GUEST_IMAGERECIPE}:do_merge_xenguestenv'}"

MC_DOIMAGE_MCDEPENDS += "mc:${MC_HOST}:${MC_GUEST}:${MC_GUEST_DEP} "

BBMULTICONFIG += "${MC_GUEST} "

ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS += "file://${TOPDIR}/${MC_GUEST}/deploy/images/${MC_GUEST_MACHINE}/${MC_GUEST_FILENAME};guestname=${MC_GUEST_NAME} "
# ---Guest Config End--- #

# ---Host Config Start--- #
MC_HOST = "host"

BBMULTICONFIG += "${MC_HOST} "
# ---Host Config End--- #
```

These variables will be used in both of the multiconf files. `MC_HOST` and
`MC_GUEST` should not be altered without renaming the conf files, but most
`MC_GUEST_*` variables can be customised if you desire.

4. Next set the contents of `multiconfig/guest.conf`:

```
TMPDIR = "${TOPDIR}/${MC_GUEST}"

MACHINE = "${MC_GUEST_MACHINE}"
DISTRO_FEATURES += " arm-autonomy-guest"

INITRAMFS_IMAGE_BUNDLE = "${MC_GUEST_INITRAMFS_IMAGE_BUNDLE}"
INITRAMFS_IMAGE = "${MC_GUEST_INITRAMFS_IMAGE}"

IMAGE_FSTYPES += "${@ 'cpio' if d.getVar('MC_GUEST_INITRAMFS_IMAGE_BUNDLE',d) else ''}"

# ANY OTHER GUEST CONFIG
```

To modify the MACHINE or INITRAMFS variables change the equivalent
config in local.conf rather than modifying this file directly. You can also
append any other config desired for the guest after "ANY OTHER GUEST CONFIG",
for example `XENGUEST_IMAGE_DISK_SIZE`.

Make sure not to change `${DEPLOY_DIR_IMAGE}` to anything other than
`${TMPDIR}/deploy/images`, as this is assumed by local.conf.

5. Lastly set the contents of `multiconfig/host.conf`:

```
TMPDIR = "${TOPDIR}/${MC_HOST}"

DISTRO_FEATURES += " arm-autonomy-host"

# ANY OTHER HOST CONFIG
```

Building the image
----------------

To build the multiconfig image the command is:
```
bitbake mc:host:arm-autonomy-host-image-minimal
```

The first time this is run you may see a warning related to the SRC_URI:
```
Unable to get checksum for xenguest-extern-guests SRC_URI entry foo.xenguest: file could not be found
```

This is expected, and only indicates that the guest image has not yet been
generated when the host parses the SRC_URI. By the time it is needed by the
host recipe fetch task it will be present.

During the build you should see that guest tasks are also being executed in
parallel. Once the build completes the guest will already be in the rootfs of
the host thanks to `ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUEST`

The final host image including the guests will be deployed in
`host/deploy/images/`


Multiple Guests
----------------

To have multiple guests with the same config the line which appends to
`ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS` just needs to pass the argument
'guestcount=#' to install symlink copies of the xenguest file on the host.
Documentation for the guestcount parameter can be found in
documentation/arm-autonomy-quickstart.md in the section titled
'Include guests directly in the host image'. This will ensure that the guest
is still only built once, despite resulting in multiple copies on the target.

If guests are required to have different configurations, each will need its own
config file, e.g. 'netguest.conf'. Ensure that the name of the conf file does
not contain any hyphens, as this will create errors when it becomes part of a
function name. In this file the values of TMPDIR, MACHINE, DISTRO_FEATURES etc.
should be the same as above, but with the prefix "MC_GUEST_*" modified to
something different to avoid collisions (e.g. MC_GUEST_2_*).

As before, your additional config for the guest type should
follow "ANY OTHER GUEST CONFIG"

In your local.conf, everything between `---Guest Config Start---` and
`---Guest Config End---` will need to be duplicated for each desired guest type.
All copies of variables that start `MC_GUEST` must be modified with the same
prefix as in the new guest config file (e.g. `MC_GUEST_2_*`).

Each chunk of guest config in local.conf has automatic guest variables
(found after the line "These variables are set automatically...").
These should all use the same prefix as their chunk in their values,
for example:
```
MC_GUEST_2_FILENAME_PREFIX = "${@ 'Image-initramfs' if d.getVar('MC_GUEST_2_INITRAMFS_IMAGE_BUNDLE',d) else '${MC_GUEST_2_IMAGERECIPE}' }"
```

Guest with provisioned disk
----------------

To add guest rootfs partition to host wic image,
set `AUTONOMY_HOST_EXTRA_PARTITION` with proper wks partition entry, e.g:

```
AUTONOMY_HOST_EXTRA_PARTITION = "part --label provisioned-guest --source rawcopy --fstype=ext4 --ondisk sda --align 1024 \
--sourceparams=file=${TOPDIR}/${MC_GUEST}/deploy/images/${MC_GUEST_MACHINE}/${MC_GUEST_FILENAME_PREFIX}-${MC_GUEST_MACHINE}.ext4"
```

inside your host.conf file.

The rest of the configuration has to be appended to guest.conf file:

```
# ANY OTHER GUEST CONFIG
XENGUEST_IMAGE_DISK_SIZE = "0"
XENGUEST_IMAGE_SRC_URI_XEN_CONFIG = "file://\${TOPDIR}/path/to/rootdisk.cfg"
XENGUEST_IMAGE_DISK_DEVICE = "_GUEST_DISK_DEVICE_"
XENGUEST_IMAGE_ROOT = "/dev/xvda"
IMAGE_ROOTFS_SIZE = "102400"
IMAGE_FSTYPES = "ext4"
```

Example content of rootdisk.cfg:

```
disk = ["phy:_GUEST_DISK_DEVICE_,xvda,w"]
```

`_GUEST_DISK_DEVICE_` should be substituted with `/dev/sdaX`,
according to wks file.
