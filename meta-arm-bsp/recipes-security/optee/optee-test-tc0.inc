# TC0 specific configuration

# Intermediate SHA with 3.11 baseline version
SRCREV = "b35df64954ef96e09c0d5573014f4d1432dbc92f"
PV = "3.11.0+git${SRCPV}"

# This is incorporated into the SRCREV above
SRC_URI_remove = " \
    file://0001-host-xtest-Adjust-order-of-including-compiler.h.patch \
    file://0002-make-remove-Wno-unsafe-loop-for-clang.patch \
    file://0003-make-remove-Wmissing-noreturn-for-clang.patch \
"

COMPATIBLE_MACHINE = "tc0"
