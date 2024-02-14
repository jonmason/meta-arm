require conf/machine/include/arm/armv8a/tune-cortexa35.inc

MACHINEOVERRIDES =. "corstone1000:"

# TF-M
PREFERRED_VERSION_trusted-firmware-m ?= "1.8.%"

# TF-A
TFA_PLATFORM = "corstone1000"
PREFERRED_VERSION_trusted-firmware-a ?= "2.9.%"
PREFERRED_VERSION_tf-a-tests ?= "2.8.%"

TFA_BL2_BINARY = "bl2-corstone1000.bin"
TFA_FIP_BINARY = "fip-corstone1000.bin"

# optee
PREFERRED_VERSION_optee-os ?= "4.1.%"

# Trusted Services
TS_PLATFORM = "arm/corstone1000"
TS_SP_SE_PROXY_CONFIG = "corstone1000"
# Include smm-gateway and se-proxy SPs into optee-os binary
MACHINE_FEATURES += "ts-smm-gateway ts-se-proxy"

# u-boot
PREFERRED_VERSION_u-boot ?= "2023.07%"
MACHINE_FEATURES += "efi"
EFI_PROVIDER ?= "grub-efi"

# Grub
LINUX_KERNEL_ARGS ?= "earlycon=pl011,0x1a510000 console=ttyAMA0,115200"
GRUB_LINUX_APPEND ?= "${LINUX_KERNEL_ARGS}"
IMAGE_CMD:wic[vardeps] += "GRUB_LINUX_APPEND"

# Linux kernel
PREFERRED_PROVIDER_virtual/kernel:forcevariable = "linux-yocto"
PREFERRED_VERSION_linux-yocto = "6.6.%"
KERNEL_IMAGETYPE = "Image.gz"
# add FF-A support in the kernel
MACHINE_FEATURES += "arm-ffa"
# enable this feature for kernel debugging
# MACHINE_FEATURES += "corstone1000_kernel_debug"
# Telling the build system which image is responsible of the generation of the initramfs rootfs
INITRAMFS_IMAGE_BUNDLE = "1"
INITRAMFS_IMAGE ?= "corstone1000-initramfs-image"
IMAGE_NAME_SUFFIX = ""

# login terminal serial port settings
SERIAL_CONSOLES ?= "115200;ttyAMA0"

WKS_FILE ?= "corstone1000-image.corstone1000.wks"

# making sure EXTRA_IMAGEDEPENDS will be used while creating the image
WKS_FILE_DEPENDS:append = " ${EXTRA_IMAGEDEPENDS}"

# prevent the kernel image from being included in the intramfs rootfs
PACKAGE_EXCLUDE += "kernel-image-*"
# Don't include kernel binary in rootfs /boot path
RRECOMMENDS:${KERNEL_PACKAGE_NAME}-base = ""

# Disable python usage in opkg-utils since it won't build with tiny config
PACKAGECONFIG:remove:pn-opkg-utils = "python"
# Disable openssl in kmod to shink the initramfs size
PACKAGECONFIG:remove:pn-kmod = "openssl"
