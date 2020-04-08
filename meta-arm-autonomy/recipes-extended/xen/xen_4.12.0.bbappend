# xen version specific patch information

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# Solve trace.c compilation error on 4.12.0
# This should only be applied for 4.12.0 (solved in greater versions)
SRC_URI += "file://4.12.0/0001-trace-fix-build-with-gcc9.patch"

# Fix problem with number of interrupts on gem5
SRC_URI_append_gem5-arm64 = " file://4.12.0/0001-xen-arm-Cap-the-number-of-interrupt-lines-for-dom0.patch"
