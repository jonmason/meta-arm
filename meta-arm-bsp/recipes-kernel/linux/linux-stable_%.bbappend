# Add support for Arm Platforms (boards or simulators)

require linux-arm-platforms.inc

#
# Corstone700 KMACHINE
#
MACHINE_KERNEL_REQUIRE ?= ""
MACHINE_KERNEL_REQUIRE_corstone700 = "linux-stable-corstone700.inc"

require ${MACHINE_KERNEL_REQUIRE}
