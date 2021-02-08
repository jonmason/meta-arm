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
    file://0009-plat-totalcompute-add-Theodul-DSU-support.patch \
    file://0010-WIP-OP-TEE-SP-declare-device-regions-in-manifest.patch \
    file://0011-WIP-OP-TEE-SP-use-CNTVCT-in-place-of-CNTVCT.patch \
    "

COMPATIBLE_MACHINE = "tc0"

OPTEEMACHINE = "totalcompute-tc0"

# Enable optee memory layout and boot logs
EXTRA_OEMAKE += " CFG_TEE_CORE_LOG_LEVEL=3"

# default disable latency benchmarks (over all OP-TEE layers)
EXTRA_OEMAKE += " CFG_TEE_BENCHMARK=n"

# Enable stats
EXTRA_OEMAKE += " CFG_WITH_STATS=y"

EXTRA_OEMAKE += " CFG_CORE_SEL2_SPMC=y"

# Copy optee manifest file and sp_layout
# This function will be modified or removed once upstream optee-os adds support
# for SEL2 SPMC config
do_install_append() {
    install -d ${D}${nonarch_base_libdir}/firmware/
    install -m 644 ${S}/core/arch/arm/plat-totalcompute/sp_layout.json \
        ${D}${nonarch_base_libdir}/firmware/
    install -m 644 ${S}/core/arch/arm/plat-totalcompute/optee_manifest.dts \
        ${D}${nonarch_base_libdir}/firmware/
}
