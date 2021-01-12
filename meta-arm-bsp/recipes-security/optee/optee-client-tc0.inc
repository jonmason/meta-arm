# TC0 specific configuration

# Intermediate SHA with 3.11 baseline version
SRCREV = "3f44b870299514ad8c6b7dee776eb2994d9c1cd4"
PV = "3.11.0+git${SRCPV}"

FILESEXTRAPATHS_prepend_tc0 := "${THISDIR}/files/optee-client/tc0:"

SRC_URI_append = " \
    file://0001-Revert-libteec-Avoid-memcpy-when-using-TEEC_TempMemo.patch \
    file://0002-Allocate-page-aligned-shared-memory-buffers.patch \
    "
