# TC0 specific configuration

# Intermediate SHA with 2.4 baseline version, required for OP-TEE SEL1 support
SRCREV = "2904b2c5361f06d35c324f37d2e71e3278d351a7"
PV = "2.4+git${SRCPV}"

FILESEXTRAPATHS_prepend_tc0 := "${THISDIR}/files/tc0:"

SRC_URI_append = " \
    file://0001-Revert-FFA-Set-and-verify-allocator-of-memory-handle.patch \
    file://0002-FF-A-Fix-to-fetch-proper-vCPU-index-for-UP-SP.patch \
    file://0003-tc0-Theodul-GICR-changes.patch \
    "

COMPATIBLE_MACHINE = "tc0"

HAFNIUM_PROJECT = "reference"
HAFNIUM_PLATFORM = "secure_tc0"
HAFNIUM_INSTALL_TARGET = "hafnium"
