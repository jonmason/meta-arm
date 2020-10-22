FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-4.14:"

SRC_URI += " \
    file://0001-arm-Add-Neoverse-N1-processor-identification.patch \
    file://0002-xen-arm-Enable-CPU-Erratum-1165522-for-Neoverse.patch \
    file://0003-xen-arm-Update-silicon-errata.txt-with-the-Neovers-A.patch \
    file://0004-xen-arm-Missing-N1-A76-A75-FP-registers-in-vCPU-cont.patch \
    file://0005-xen-arm-Throw-messages-for-unknown-FP-SIMD-implement.patch \
    "
