# Total Compute (tc) specific configuration for optee-os and optee-os-tadevkit

# Intermediate SHA with 3.14 baseline version
# This has TC0 platform support
SRCREV = "e4f34e786135079160697d88212591105a65fbce"
PV = "3.14.0+git${SRCPV}"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/optee-os/tc:"
SRC_URI:append:tc = " \
    file://sp_layout.json \
    file://0001-WIP-Enable-managed-exit.patch \
    file://0003-ffa-Update-function-ID-according-to-FFA-v1.1-spec.patch \
    file://0001-plat-totalcompute-Specify-managed-exit-in-the-partit.patch \
    "

COMPATIBLE_MACHINE = "(tc?)"

OPTEEMACHINE:tc0 = "totalcompute-tc0"
OPTEEMACHINE:tc1 = "totalcompute-tc1"

