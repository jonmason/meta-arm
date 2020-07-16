# FVP common parameters

#
# Capturing FVP common configurations (Armv8-A Base Platform FVP and
# Armv8-A Foundation Platform).
#

TUNE_FEATURES = "aarch64"

require conf/machine/include/arm/arch-armv8a.inc

MACHINE_FEATURES = "optee"

KERNEL_IMAGETYPE = "Image"

IMAGE_CLASSES += "image_types_disk_img"
IMAGE_FSTYPES += "disk.img"

# Disk image configuration
# We don't use the first partition
DISK_IMG_PARTITION1_SIZE = "128"
DISK_IMG_PARTITION1_FSTYPE = ""
DISK_IMG_PARTITION1_CONTENT = ""

# Second partition is used for rootfs
DISK_IMG_PARTITION2_SIZE = "2048"
DISK_IMG_PARTITION2_FSTYPE = "ext4"
DISK_IMG_PARTITION2_CONTENT = "rootfs"

# Empty third partition (8G - 2048M - 128M)
DISK_IMG_PARTITION3_SIZE = "6016"
DISK_IMG_PARTITION3_FSTYPE = ""
DISK_IMG_PARTITION3_CONTENT = ""

SERIAL_CONSOLES = "115200;ttyAMA0"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-yocto"
PREFERRED_VERSION_linux-yocto ?= "5.4%"

EXTRA_IMAGEDEPENDS += "virtual/trusted-firmware-a u-boot"

# FVP u-boot configuration
UBOOT_MACHINE = "vexpress_aemv8a_semi_defconfig"
