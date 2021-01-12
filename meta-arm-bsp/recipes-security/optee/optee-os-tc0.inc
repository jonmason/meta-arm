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

COMPATIBLE_MACHINE = "tc0"

OPTEEMACHINE = "totalcompute-tc0"
