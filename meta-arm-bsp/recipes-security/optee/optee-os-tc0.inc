# TC0 specific configuration

# Intermediate SHA with 3.11 baseline version
SRCREV = "3284d935bc7e7bf7abfb5b19394a387d975d6dd4"
PV = "3.11.0+git${SRCPV}"

# This is incorporated into the SRCREV above
SRC_URI_remove = " \
    file://0001-libutils-provide-empty-__getauxval-implementation.patch \
    file://0002-link.mk-implement-support-for-libnames-after-libgcc-.patch \
    file://0003-ta_dev_kit.mk-make-sure-that-libutils-is-linked-seco.patch \
    "

FILESEXTRAPATHS_prepend_tc0 := "${THISDIR}/files/optee-os/tc0:"

SRC_URI_append = " \
    file://0001-core-SPMC-update-for-FF-A-version-1.0.patch \
    file://0002-core-add-thread_smccc.patch \
    file://0003-core-enable-SPCI-with-SPM-Core-at-S-EL2.patch \
    file://0004-core-fixes-to-align-with-upstream-hafnium.patch \
    file://0005-core-arm-Total-Compute-platform-support.patch \
    file://0006-plat-totalcompute-Add-support-for-S-EL2-SPMC.patch \
    file://0007-plat-totalcompute-add-optee-manifest-file-and-sp-lay.patch \
    file://0008-plat-totalcompute-define-tzdram-start-address-for-S-.patch \
    "

COMPATIBLE_MACHINE = "tc0"

OPTEEMACHINE = "totalcompute-tc0"
