# Extra machine settings for n1sdp

# We need to extent the wks search path to be able to find the wks file set in
# ARM_AUTONOMY_WKS_FILE.
WKS_SEARCH_PATH_prepend := "${ARM_AUTONOMY_ARM_BSP_DYNAMIC_DIR}/wic:"

ARM_AUTONOMY_WKS_FILE ?= "arm-autonomy-n1sdp-efidisk.wks.in"
WKS_FILE = "${ARM_AUTONOMY_WKS_FILE}"

# Set the wks guest partition size and unit. It must be aligned with the sum of
# all XENGUEST_IMAGE_DISK_SIZE set for the guests. By default, LVM2 metadata is
# 1 MiB per physical volume, hence it needs to be taken into account when
# setting GUEST_PART_SIZE. The XENGUEST_IMAGE_DISK_SIZE default value is 4GiB.
GUEST_PART_SIZE ?= "4097"
GUEST_PART_SIZE_UNIT ?= "M"

# The GRUB_CFG_FILE affects arm-autonomy-n1sdp-efidisk.wks.in file
GRUB_CFG_FILE ?= "${ARM_AUTONOMY_ARM_BSP_DYNAMIC_DIR}/wic/arm-autonomy-n1sdp-grub.cfg"

# From arm-autonomy-n1sdp-efidisk.wks.in, the /boot partition is /dev/sda1, and
# the "/" partition is /dev/sda2.
XENGUEST_MANAGER_VOLUME_DEVICE ?= "/dev/sda3"

XENGUEST_NETWORK_BRIDGE_MEMBERS ?= "eth0"

# The XEN_DEVICETREE_DEPEND and XEN_DEVICETREE_DTBS variables aftect the
# xen-devicetree.bb recipe
XEN_DEVICETREE_DEPEND = "virtual/trusted-firmware-a:do_deploy"
XEN_DEVICETREE_DTBS ?= "n1sdp-single-chip.dtb"
# XEN_MOD_DEVICETREE_DTBS are the generated devicetrees for Xen. By default the
# xen-devicetree.bb recipe adds '-xen' suffix to it
XEN_MOD_DEVICETREE_DTBS ?= "n1sdp-single-chip-xen.dtb"

# When generating the wic image we need to have the xen deployed
do_image_wic[depends] += "xen:do_deploy"

# Select the extra files to be included in the boot partition
IMAGE_EFI_BOOT_FILES += "xen-n1sdp.efi;xen.efi"
IMAGE_EFI_BOOT_FILES += "${XEN_MOD_DEVICETREE_DTBS}"

# When alternate-kernel DISTRO_FEATURE is present we set the linux-linaro-arm-rt
# by default
PREFERRED_PROVIDER_alternate/kernel ?= "\
${@bb.utils.contains('DISTRO_FEATURES', 'alternate-kernel', \
'linux-linaro-arm-rt', '', d)}"

KERNEL_PACKAGE_NAME_alternate/kernel ?= "kernel-rt"
# When alternate-kernel DISTRO_FEATURE is present we set the kernel-rt by
# default
KERNEL_PACKAGE_NAME_pn-linux-linaro-arm-rt = "\
${@ d.getVar('KERNEL_PACKAGE_NAME_alternate/kernel') \
if bb.utils.contains('DISTRO_FEATURES', 'alternate-kernel', True, False, d) \
else 'kernel' }"

# Relative path from DEPLOY_DIR_IMAGE of the Kernel PREEMPT_RT deployed Image
KERNEL_RT_IMAGE ?= "kernel-rt/Image-n1sdp.bin;Image-preempt-rt"
# Only include the Kernel PREEMPT_RT Image if we are building with
# alternate-kernel DISTRO_FEATURE
IMAGE_EFI_BOOT_FILES += "\
${@ d.getVar('KERNEL_RT_IMAGE',d) or '' \
if bb.utils.contains('DISTRO_FEATURES', 'alternate-kernel', True, False, d) and \
d.getVar('PREFERRED_PROVIDER_alternate/kernel') else ''}"
