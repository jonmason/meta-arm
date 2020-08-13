# Common configuration for all Corstone700 machines

require conf/machine/include/tune-cortexa32.inc

MACHINEOVERRIDES =. "corstone700:"

SERIAL_CONSOLES ?= "115200;ttyAMA0"

PREFERRED_PROVIDER_virtual/kernel_corstone700 = "linux-stable"
PREFERRED_VERSION_linux-stable ?= "5.6%"

VIRTUAL-RUNTIME_dev_manager = "busybox-mdev"

WKS_FILE ?= "arm-reference-image.corstone700.wks"
