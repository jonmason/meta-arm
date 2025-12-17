require recipes-bsp/uefi/edk2-firmware.inc

SRCREV_edk2           ?= "46548b1adac82211d8d11da12dd914f41e7aa775"
SRCREV_edk2-platforms ?= "675f692ace4ae501c7f6f700cff364b13960e74e"

SRC_URI += "file://0001-BaseTools-tools_def-Use-LLD-to-link-ACPI-table-binar.patch \
            file://0001-ArmPkg-Fix-errors-in-MiscChassisManufacturerFunction.patch"
