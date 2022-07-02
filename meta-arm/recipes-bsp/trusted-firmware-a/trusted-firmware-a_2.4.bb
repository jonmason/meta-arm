require trusted-firmware-a.inc

# Use TF-A for version
SRCREV_FORMAT = "tfa"

# TF-A v2.4
SRCREV_tfa = "e2c509a39c6cc4dda8734e6509cdbe6e3603cdfc"

LIC_FILES_CHKSUM += "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

# mbed TLS v2.24.0
SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls;branch=master"
SRCREV_mbedtls = "523f0554b6cdc7ace5d360885c3f5bbcc73ec0e8"

LIC_FILES_CHKSUM_MBEDTLS = "file://mbedtls/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI_append = "file://0003-xlat-tables-v2-remove-tautological-assert.patch"
