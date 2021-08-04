# TC0 specific configuration

# Intermediate SHA with 3.14 baseline version
# This has TC0 platform support
SRCREV = "49dbb9ef65643c4322cf3f848910fa880d1c02f6"
PV = "3.14.0+git${SRCPV}"

FILESEXTRAPATHS:prepend:tc0 := "${THISDIR}/files/optee-os/tc0:"
SRC_URI:append = " \
    file://sp_layout.json \
    file://0001-WIP-Enable-managed-exit.patch \
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

# Copy optee manifest file
do_install:append() {
    install -d ${D}${nonarch_base_libdir}/firmware/
    install -m 644 ${WORKDIR}/sp_layout.json ${D}${nonarch_base_libdir}/firmware/
    install -m 644 \
        ${S}/core/arch/arm/plat-totalcompute/fdts/optee_sp_manifest.dts \
        ${D}${nonarch_base_libdir}/firmware/
}
