#
# Trusted firmware-A 2.3
#

require trusted-firmware-a.inc

SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https;name=tfa"

# Use TF-A for version
SRCREV_FORMAT = "tfa"

# TF-A v2.3
SRCREV_tfa = "ecd27ad85f1eba29f6bf92c39dc002c85b07dad5"

S = "${WORKDIR}/git"

LIC_FILES_CHKSUM += "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

#
# mbed TLS source
# Those are used in trusted-firmware-a.inc if TFA_MBEDTLS is set to 1
#

SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls;branch=mbedtls-2.18"

# mbed TLS v2.18.1
SRCREV_mbedtls = "ca933c7e0c9e84738b168b6b0feb89af4183a60a"

LIC_FILES_CHKSUM_MBEDTLS = " \
    file://mbedtls/apache-2.0.txt;md5=3b83ef96387f14655fc854ddc3c6bd57 \
    file://mbedtls/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
    "
