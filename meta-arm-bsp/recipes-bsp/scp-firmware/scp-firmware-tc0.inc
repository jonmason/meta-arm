# TC0 specific SCP configuration

# Intermediate SHA with 2.7 baseline version, required for Theodul DSU
SRCREV = "a841e17b9a11784cddd96f3becdd7e4c54cfb44b"
PV = "2.7+git${SRCPV}"

FILESEXTRAPATHS_prepend_tc0 := "${THISDIR}/files/tc0:"

SRC_URI_append = " \
    file://0001-product-tc0-add-clock-and-dvfs-support-for-all-cores.patch \
    file://0002-module-cmn_booker-amend-CFGM-base-address.patch \
    "

COMPATIBLE_MACHINE = "tc0"

SCP_PLATFORM = "tc0"
FW_TARGETS = "scp"
