require conf/machine/include/arm/armv8a/tune-cortexa35.inc

MACHINEOVERRIDES =. "corstone1000:"

# TF-A
TFA_PLATFORM = "corstone1000"
PREFERRED_VERSION_trusted-firmware-a ?= "2.5%"
EXTRA_IMAGEDEPENDS += "virtual/trusted-firmware-a"

# TF-M
PREFERRED_VERSION_trusted-firmware-m ?= "1.4%"
TFM_PLATFORM = "arm/corstone1000"
EXTRA_IMAGEDEPENDS += "virtual/trusted-firmware-m"

# u-boot
PREFERRED_VERSION_u-boot ?= "2021.07"
EXTRA_IMAGEDEPENDS += "u-boot"

UBOOT_CONFIG ??= "EFI"
UBOOT_CONFIG[EFI] = "corstone1000_defconfig"
UBOOT_ENTRYPOINT  = "0x80000000"
UBOOT_LOADADDRESS = "0x80000000"
UBOOT_BOOTARGS = "earlycon=pl011,0x1a510000 console=ttyAMA0 loglevel=9"
UBOOT_ARCH = "arm"
UBOOT_EXTLINUX = "0"

# optee
EXTRA_IMAGEDEPENDS += "optee-os"
OPTEE_ARCH = "arm64"
OPTEE_BINARY = "tee-pager_v2.bin"

# Linux kernel
PREFERRED_PROVIDER_virtual/kernel:forcevariable = "linux-yocto"
PREFERRED_VERSION_linux-yocto = "5.10%"
KERNEL_IMAGETYPE = "Image"

INITRAMFS_IMAGE_BUNDLE ?= "1"

#telling the build system which image is responsible of the generation of the initramfs rootfs
INITRAMFS_IMAGE = "corstone1000-initramfs-image"

# enable this feature for kernel debugging
# MACHINE_FEATURES += "corstone1000_kernel_debug"

# login terminal serial port settings
SERIAL_CONSOLES ?= "115200;ttyAMA0"

# making sure EXTRA_IMAGEDEPENDS will be used while creating the image
WKS_FILE_DEPENDS:append = " ${EXTRA_IMAGEDEPENDS}"

WKS_FILE ?= "corstone1000-image.corstone1000.wks"
