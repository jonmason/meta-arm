# Common configuration for all Corstone700 machines

require conf/machine/include/arm/armv8a/tune-cortexa32.inc

MACHINEOVERRIDES =. "corstone700:"

TFA_PLATFORM = "corstone700"

SERIAL_CONSOLES ?= "115200;ttyAMA0"

PREFERRED_PROVIDER_virtual/kernel = "linux-yocto"
PREFERRED_VERSION_linux-yocto ?= "5.6%"

PREFERRED_VERSION_trusted-firmware-a ?= "2.5%"

PREFERRED_VERSION_gcc-arm-none-eabi-native ?= "9-2020-q2-update"

PREFERRED_PROVIDER_virtual/control-processor-firmware ?= "boot-firmware"

EXTRA_IMAGEDEPENDS += " \
                      virtual/trusted-firmware-a          \
                      external-system                     \
                      u-boot                              \
                      virtual/control-processor-firmware  \
                      "

WKS_FILE_DEPENDS:append = " ${EXTRA_IMAGEDEPENDS}"

WKS_FILE ?= "arm-reference-image.corstone700.wks"

VIRTUAL-RUNTIME_dev_manager = "busybox-mdev"

UBOOT_MACHINE ?= "corstone700_defconfig"
PREFERRED_VERSION_u-boot ?= "2020.04"
