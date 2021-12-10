require trusted-firmware-a.inc

# TF-A v2.6
SRCREV_tfa = "a1f02f4f3daae7e21ee58b4c93ec3e46b8f28d15"

LIC_FILES_CHKSUM += "file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"

# mbed TLS v2.26.0
SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls;branch=master"
SRCREV_mbedtls = "e483a77c85e1f9c1dd2eb1c5a8f552d2617fe400"

LIC_FILES_CHKSUM_MBEDTLS = "file://mbedtls/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"
