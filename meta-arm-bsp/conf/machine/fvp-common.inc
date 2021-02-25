# FVP common parameters

#
# Capturing FVP common configurations (Armv8-A Base Platform FVP,
# Armv8-A Foundation Platform and Armv7-A Base Platform FVP).
#

MACHINE_FEATURES = "optee"

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
PREFERRED_VERSION_linux-yocto ?= "5.10%"

PREFERRED_VERSION_u-boot ?= "2021.01"
PREFERRED_VERSION_trusted-firmware-a ?= "2.4%"

EXTRA_IMAGEDEPENDS += "virtual/trusted-firmware-a u-boot"

# As this is a virtual target that will not be used in the real world there is
# no need for real SSH keys.  Disable rng-tools (which takes too long to
# initialise) and install the pre-generated keys.
PACKAGECONFIG_remove_pn-openssh = "rng-tools"
MACHINE_EXTRA_RRECOMMENDS += "ssh-pregen-hostkeys"
