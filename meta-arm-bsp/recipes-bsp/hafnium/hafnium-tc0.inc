# TC0 specific configuration

# Intermediate SHA with 2.4 baseline version
SRCREV = "ee68c5494dea5c5a59aa02af46b35ab3d949672e"
PV = "2.4+git${SRCPV}"

FILESEXTRAPATHS_prepend_tc0 := "${THISDIR}/files/tc0:"

SRC_URI_append = " \
    file://0001-FF-A-Register-secondary-core-entry-point-at-SPMC-ini.patch \
    file://0002-FF-A-Cold-boot-and-wake-up-from-suspend.patch \
    file://0003-FF-A-Respond-to-PSCI_CPU_OFF-from-SPMD.patch \
    "

COMPATIBLE_MACHINE = "tc0"

HAFNIUM_PROJECT = "reference"
HAFNIUM_PLATFORM = "secure_tc0"
HAFNIUM_INSTALL_TARGET = "hafnium"
