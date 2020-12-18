# Include machine specific configurations for UEFI EDK2

MACHINE_EDK2_REQUIRE ?= ""

MACHINE_EDK2_REQUIRE_fvp-base = "edk2-firmware-fvp-base.inc"
MACHINE_EDK2_REQUIRE_sgi575 = "edk2-firmware-sgi575.inc"

require ${MACHINE_EDK2_REQUIRE}
