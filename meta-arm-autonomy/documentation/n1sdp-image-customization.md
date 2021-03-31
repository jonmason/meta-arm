Customizing Arm Autonomy Host image layout for N1SDP
====================================================

When buiding with `DISTRO_FEATURES += "arm-autonomy-host"` the user can
perform a couple of customizations in the generated wic image:

1. Set the guest partition size (default: 4iG) via `GUEST_PART_SIZE` and
   `GUEST_PART_SIZE_UNIT` (M or G) variables to be set in any conf file. The
   value of these variables should be aligned with the sum of all
   XENGUEST_IMAGE_DISK_SIZE set for the guests. By default, LVM2 metadata is
   1 MiB per physical volume, hence it needs to be taken into account when
   setting GUEST_PART_SIZE.

2. Set the boot partition size (default: 100M) via `BOOT_PART_SIZE` and
   `BOOT_PART_SIZE_UNIT` (M or G) variables in any conf file. The default
   bootimg is ~44M so 100M leaves just over 50M of free space.

3. The wic image partition layout and contents with a custom wks file via
   `ARM_AUTONOMY_WKS_FILE` variable (default:
   arm-autonomy-n1sdp-efidisk.wks.in which is affected by GUEST_PART_SIZE,
   GUEST_PART_SIZE_UNIT, BOOT_PART_SIZE, BOOT_PART_SIZE_UNIT and
   GRUB_CFG_FILE variables).

4. Custom grub.cfg file via `GRUB_CFG_FILE` (default:
   arm-autonomy-n1sdp-grub.cfg) variable to be set in any conf file. The full
   path or relative to `ARM_AUTONOMY_WKS_FILE` should be set.

The `arm-autonomy-n1sdp-efidisk.wks.in` and `arm-autonomy-n1sdp-grub.cfg` files
are located at `meta-arm-autonomy/dynamic-layers/meta-arm-bsp/wic`.

Other variables can also be customized to set what files need to be included
in the wic image boot partition. Please refer to
`meta-arm-autonomy/dynamic-layers/meta-arm-bsp/conf/machine/n1sdp-extra-settings.inc`
for more details.
