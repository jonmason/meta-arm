MACHINE_TFAG_REQUIRE ?= ""
MACHINE_TFAG_REQUIRE:qemuarm-secureboot = "trusted-firmware-a-qemuarm-secureboot.inc"
MACHINE_TFAG_REQUIRE:qemuarm64-secureboot = "trusted-firmware-a-qemuarm64-secureboot.inc"
MACHINE_TFAG_REQUIRE:qemu-generic-arm64 = "trusted-firmware-a-qemu-generic-arm64.inc"

require ${MACHINE_TFAG_REQUIRE}
