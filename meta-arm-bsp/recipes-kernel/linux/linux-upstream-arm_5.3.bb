# Add support for Upstream Kernel for Arm Platforms (boards or simulators)

SUMMARY = "Linux Kernel Upstream, supported by Arm/Linaro"

require recipes-kernel/linux/linux-upstream-arm-platforms.inc

SRCREV = "v${PV}"
LINUX_VERSION ?= "${PV}"
