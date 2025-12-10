require recipes-security/optee/optee-test.inc

# v4.8.0
SRCREV = "6569cd7b13e1b37b37069e090d592adca7d3926d"
PV .= "+git"

LIC_FILES_CHKSUM = "file://LICENSE.md;md5=a8fa504109e4cd7ea575bc49ea4be560"

# Include ffa_spmc test group if the SPMC test is enabled.
# Supported after op-tee v3.20
EXTRA_OEMAKE:append = "${@bb.utils.contains('MACHINE_FEATURES', 'optee-spmc-test', \
                                        ' CFG_SPMC_TESTS=y CFG_SECURE_PARTITION=y', '' , d)}"

RDEPENDS:${PN} += "${@bb.utils.contains('MACHINE_FEATURES', 'optee-spmc-test', \
                                              ' arm-ffa-user', '' , d)}"

# Not a release recipe, try our hardest to not pull this in implicitly
DEFAULT_PREFERENCE = "-1"

CFLAGS += "-Wno-error=unterminated-string-initialization"
