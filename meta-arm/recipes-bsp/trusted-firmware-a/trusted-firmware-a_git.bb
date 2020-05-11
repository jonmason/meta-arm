# Trusted firmware-A points a commit rather a tag
#
# This is only a base receipt and should be bbextended with suitable SRCREV_tfa
# and SRCREV_MBEDTLS and target TFA_* variables

# Never select this if another version is available
DEFAULT_PREFERENCE = "-1"

require trusted-firmware-a.inc

SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https;name=tfa"

# Use TF-A for version
SRCREV_FORMAT = "tfa"

S = "${WORKDIR}/git"

LIC_FILES_CHKSUM = "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

#
# mbed TLS source
# Those are used in trusted-firmware-a.inc if TFA_MBEDTLS is set to 1
#

SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls"

LIC_FILES_CHKSUM_MBEDTLS += " \
    file://mbedtls/apache-2.0.txt;md5=3b83ef96387f14655fc854ddc3c6bd57 \
    file://mbedtls/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
    "

