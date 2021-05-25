require trusted-firmware-a.inc

# Use TF-A for version
SRCREV_FORMAT = "tfa"

# TF-A v2.5
SRCREV_tfa = "1e13c500a0351ac4b55d09a63f7008e2438550f8"

LIC_FILES_CHKSUM += "file://docs/license.rst;md5=713afe122abbe07f067f939ca3c480c5"

# mbed TLS v2.26.0
SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls;branch=master"
SRCREV_mbedtls = "e483a77c85e1f9c1dd2eb1c5a8f552d2617fe400"

LIC_FILES_CHKSUM_MBEDTLS = "file://mbedtls/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"
