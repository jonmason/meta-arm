# TC0 specific configuration

# Intermediate SHA with 2.4 baseline version, required for OP-TEE SEL1 support
SRCREV = "fe7f737ec20add15d49c587ebeb55f7ea0118226"
PV = "2.4+git${SRCPV}"

FILESEXTRAPATHS_prepend_tc0 := "${THISDIR}/files/tc0:"

SRC_URI_append = " \
    file://0001-FF-A-Register-secondary-core-entry-point-at-SPMC-ini.patch \
    file://0002-FF-A-Cold-boot-and-wake-up-from-suspend.patch \
    file://0003-FF-A-Respond-to-PSCI_CPU_OFF-from-SPMD.patch \
    file://0004-tc0-Add-Theodul-DSU-support.patch \
    "

COMPATIBLE_MACHINE = "tc0"

HAFNIUM_PROJECT = "reference"
HAFNIUM_PLATFORM = "secure_tc0"
HAFNIUM_INSTALL_TARGET = "hafnium"
