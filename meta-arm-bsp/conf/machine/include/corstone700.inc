# Common configuration for all Corstone700 machines

require conf/machine/include/tune-cortexa32.inc

MACHINEOVERRIDES =. "corstone700:"

TFA_PLATFORM = "corstone700"

SERIAL_CONSOLES ?= "115200;ttyAMA0"

PREFERRED_PROVIDER_virtual/kernel_corstone700 = "linux-yocto"
PREFERRED_VERSION_linux-yocto ?= "5.6%"

PREFERRED_PROVIDER_virtual/trusted-firmware-a ?= "trusted-firmware-a"
PREFERRED_VERSION_trusted-firmware-a ?= "2.3%"

PREFERRED_PROVIDER_virtual/control-processor-firmware ?= "scp-firmware"
PREFERRED_VERSION_control-processor-firmware ?= "2.6.0"

EXTRA_IMAGEDEPENDS += " \
                      virtual/trusted-firmware-a          \
                      external-system                     \
                      u-boot                              \
                      virtual/control-processor-firmware  \
                      "

WKS_FILE_DEPENDS_append = " ${EXTRA_IMAGEDEPENDS}"

WKS_FILE ?= "arm-reference-image.corstone700.wks"

VIRTUAL-RUNTIME_dev_manager = "busybox-mdev"

UBOOT_MACHINE ?= "corstone700_defconfig"
PREFERRED_VERSION_u-boot ?= "2020.04"