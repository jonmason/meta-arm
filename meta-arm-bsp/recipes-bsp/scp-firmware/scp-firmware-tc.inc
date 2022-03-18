# TC specific SCP configuration

# Intermediate SHA with 2.9 baseline version
# This has support for SCP features MPMM/POWER/PERFORMANCE for TC0
SRCREV = "027b567fde5e3767fb1678bda28cf59fa7aac06d"
PV = "2.9.0+git${SRCPV}"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/tc:"
SRC_URI:append:tc = " \
    file://0001-tc0-fix-sensor-data-api-call.patch \
    file://0002-tc0-fix-mpmm-config.patch \
    file://0003-tc0-rename-platform-variant-to-platform-feature-set.patch \
    file://0004-tc0-support-platform-feature-set-options-in-firmware.patch \
    "

COMPATIBLE_MACHINE = "(tc?)"

SCP_PLATFORM:tc0 = "tc0"
SCP_PLATFORM:tc1 = "tc1"
FW_TARGETS = "scp"
