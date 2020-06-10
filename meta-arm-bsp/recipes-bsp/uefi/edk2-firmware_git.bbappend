# Include machine specific configurations for UEFI EDK2

MACHINE_EDK2_REQUIRE ?= ""

MACHINE_EDK2_REQUIRE_n1sdp = "edk2-firmware-n1sdp.inc"

require ${MACHINE_EDK2_REQUIRE}
