#
# Trusted firmware-A 2.2
#

require trusted-firmware-a.inc

SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https;name=tfa"

# Use TF-A for version
SRCREV_FORMAT = "tfa"

# TF-A v2.2
SRCREV_tfa = "7192b956bde11652a835eee0724dca0e403fee90"

S = "${WORKDIR}/git"

LIC_FILES_CHKSUM += "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

#
# mbed TLS source
# Those are used in trusted-firmware-a.inc if TFA_MBEDTLS is set to 1
#

SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls;branch=mbedtls-2.16"

# mbed TLS v2.16.2
SRCREV_mbedtls = "d81c11b8ab61fd5b2da8133aa73c5fe33a0633eb"

LIC_FILES_CHKSUM_MBEDTLS = " \
    file://mbedtls/apache-2.0.txt;md5=3b83ef96387f14655fc854ddc3c6bd57 \
    file://mbedtls/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
    "
