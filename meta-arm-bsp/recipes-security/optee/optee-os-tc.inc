# TC0 specific configuration

# Total Compute (tc) specific configuration for optee-os and optee-os-tadevkit

COMPATIBLE_MACHINE = "(tc?)"

OPTEEMACHINE:tc2 = "totalcompute-tc2"

# Enable optee memory layout and boot logs
EXTRA_OEMAKE += " CFG_TEE_CORE_LOG_LEVEL=3"

# default disable latency benchmarks (over all OP-TEE layers)
EXTRA_OEMAKE += " CFG_TEE_BENCHMARK=n"

# Enable stats
EXTRA_OEMAKE += " CFG_WITH_STATS=y"

EXTRA_OEMAKE += " CFG_CORE_SEL2_SPMC=y"

FILESEXTRAPATHS:prepend := "${THISDIR}/optee-os/tc2:"
SRC_URI += "file://sp_layout.json"

# Copy optee manifest file
do_install:append() {
    install -d ${D}${nonarch_base_libdir}/firmware/
    install -m 644 ${UNPACKDIR}/sp_layout.json ${D}${nonarch_base_libdir}/firmware/
    install -m 644 \
        ${S}/core/arch/arm/plat-totalcompute/fdts/optee_sp_manifest.dts \
        ${D}${nonarch_base_libdir}/firmware/
}
