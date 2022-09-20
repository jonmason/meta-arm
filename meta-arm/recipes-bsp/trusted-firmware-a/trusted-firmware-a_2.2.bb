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

LIC_FILES_CHKSUM = "file://docs/license.rst;md5=189505435dbcdcc8caa63c46fe93fa89"

SRC_URI[tfa.md5sum] = "75c8f4958fb493d9bd7a8e5a9636ec18"
SRC_URI[tfa.sha256sum] = "7c4c00a4f28d3cfbb235fd1a1fb28c4d2fc1d657c9301686e7d8824ef575d059"

#
# mbed TLS source
# Those are used in trusted-firmware-a.inc if TFA_MBEDTLS is set to 1
#

SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls;branch=archive/mbedtls-2.16"

# mbed TLS v2.16.2
SRCREV_mbedtls = "d81c11b8ab61fd5b2da8133aa73c5fe33a0633eb"

LIC_FILES_CHKSUM_MBEDTLS += " \
    file://mbedtls/apache-2.0.txt;md5=3b83ef96387f14655fc854ddc3c6bd57 \
    file://mbedtls/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
    "

SRC_URI[mbedtls.md5sum] = "37cdec398ae9ebdd4640df74af893c95"
SRC_URI[mbedtls.sha256sum] = "a6834fcd7b7e64b83dfaaa6ee695198cb5019a929b2806cb0162e049f98206a4"
