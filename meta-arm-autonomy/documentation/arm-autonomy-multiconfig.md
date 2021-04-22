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

Here are the steps required to make the project build both the host and any
number of guests as required.

1. Create a new directory under `conf/` named `multiconfig/`

2. Create two new files in this directory:
`multiconfig/host.conf`
`multiconfig/guest.conf`
These files will contain any configurations that a specific to either the
host or the guest

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

# These variables are set automatically, don't edit them!
MC_GUEST_FILENAME_PREFIX = "${@ 'Image-initramfs' if d.getVar('MC_GUEST_INITRAMFS_IMAGE_BUNDLE',d) else '${MC_GUEST_IMAGERECIPE}' }"

MC_GUEST_FILENAME = "${MC_GUEST_FILENAME_PREFIX}-${MC_GUEST_MACHINE}.xenguest"

MC_GUEST_DEP = "${@ 'virtual/kernel:do_deploy' if d.getVar('MC_GUEST_INITRAMFS_IMAGE_BUNDLE',d) else '${MC_GUEST_IMAGERECIPE}:do_image_complete'}"

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

This contents shouldn't be changed directly, rather change the equivalent
config in local.conf. You can append any other config desired for the
guest at this point, for example `XENGUEST_IMAGE_DISK_SIZE`

Make sure not to change `${DEPLOY_DIR_IMAGE}` to anything other than
`${TMPDIR}/deploy/images`, as this is assumed by local.conf.

5. Lastly set the contents of `multiconfig/host.conf`:

```
TMPDIR = "${TOPDIR}/${MC_HOST}"

DISTRO_FEATURES += " arm-autonomy-host"
```

Building the image
----------------

To build the multiconfig image the command is:
```
bitbake mc:host:arm-autonomy-host-image-minimal
```

You should see that this triggers guest tasks to be built in
parallel. Once the build completes the guest will already be in the
rootfs of the host thanks to `ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUEST`

The deployed image including the guest will be in `host/deploy/images/`


Multiple Guests
----------------

To have multiple guests with the same config the line which appends to
`ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUEST` just needs to be duplicated with
a different guestname.

To have different config for each guest, each will need its own config
file similar to guest.conf, ensuring TMPDIR is set to a different path,
and everything between `---Guest Config Start---` and
`---Guest Config End---` will need to be duplicated.

Any copies of variables that start `MC_GUEST` must be altered to avoid
collisions (e.g. `MC_GUEST_2_*`), and the name of the conf file must also
be added to BBMULTICONFIG.


Guest with provisioned disk
----------------

To add guest rootfs partition to host wic image,
set `AUTONOMY_HOST_EXTRA_PARTITION` with proper wks partition entry, e.g:

```
AUTONOMY_HOST_EXTRA_PARTITION = "part --label provisioned-guest --source rawcopy --fstype=ext4 --ondisk sda --align 1024 \
--sourceparams=file=${TOPDIR}/${MC_GUEST}/deploy/images/${MC_GUEST_MACHINE}/${MC_GUEST_FILENAME_PREFIX}-${MC_GUEST_MACHINE}.ext4"
```

inside host.conf file.

The rest of the configuration has to be appended to guest.conf file:

```
XENGUEST_IMAGE_DISK_SIZE = "0"
XENGUEST_IMAGE_SRC_URI_XEN_CONFIG = "file://\${TOPDIR}/path/to/rootdisk.cfg"
XENGUEST_IMAGE_DISK_DEVICE = "_GUEST_DISK_DEVICE_"
XENGUEST_IMAGE_ROOT = "/dev/xvda"
IMAGE_ROOTFS_SIZE = "102400"
IMAGE_FSTYPES = "ext4"
```

content of rootdisk.cfg"

```
disk = ["phy:_GUEST_DISK_DEVICE_,xvda,w"]
```

`_GUEST_DISK_DEVICE_` should be substituted with `/dev/sdaX`,
according to wks file.
