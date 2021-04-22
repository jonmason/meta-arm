#
# Trusted firmware-A 2.3
#

require trusted-firmware-a.inc

# Use TF-A for version
SRCREV_FORMAT = "tfa"

# TF-A v2.3
SRCREV_tfa = "ecd27ad85f1eba29f6bf92c39dc002c85b07dad5"

LIC_FILES_CHKSUM += "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

SRC_URI += "file://0001-fdts-a5ds-Fix-for-the-system-timer-issue.patch"

#
# mbed TLS source
# Those are used in trusted-firmware-a.inc if TFA_MBEDTLS is set to 1
#

SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls;tag=v2.24.0"

FILESEXTRAPATHS_prepend := "${THISDIR}/${BP}:"
SRC_URI += " \
    file://0001-make-link-compiler-rt-builtins-when-32-bit-2-3.patch \
    "

# mbed TLS v2.18.1
SRCREV_mbedtls = "v2.24.0"

LIC_FILES_CHKSUM_MBEDTLS = " \
    file://mbedtls/apache-2.0.txt;md5=3b83ef96387f14655fc854ddc3c6bd57 \
    file://mbedtls/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
    "
