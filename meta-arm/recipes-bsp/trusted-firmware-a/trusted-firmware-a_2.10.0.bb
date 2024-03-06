require recipes-bsp/trusted-firmware-a/trusted-firmware-a.inc

# TF-A v2.10.0
SRCREV_tfa = "b6c0948400594e3cc4dbb5a4ef04b815d2675808"

LIC_FILES_CHKSUM += "file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"

# mbedtls-3.4.1
SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls;branch=master"
SRCREV_mbedtls = "72718dd87e087215ce9155a826ee5a66cfbe9631"

LIC_FILES_CHKSUM_MBEDTLS = "file://mbedtls/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"
