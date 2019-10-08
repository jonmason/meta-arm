#
# Trusted firmware-A 2.1
#
SRC_URI = " \
    git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https;name=tfa \
    git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls \
    "

SRCREV_FORMAT = "tfa_mbedtls"

# TF-A v2.1
SRCREV_tfa = "e1286bdb968ee74fc52f96cf303a4218e1ae2950"
# mbed TLS v2.16.2
SRCREV_mbedtls = "d81c11b8ab61fd5b2da8133aa73c5fe33a0633eb"


S = "${WORKDIR}/git"

LIC_FILES_CHKSUM = " \
    file://license.rst;md5=c709b197e22b81ede21109dbffd5f363 \
    file://mbedtls/apache-2.0.txt;md5=3b83ef96387f14655fc854ddc3c6bd57 \
    file://mbedtls/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
    "

SRC_URI[tfa.md5sum] = "75c8f4958fb493d9bd7a8e5a9636ec18"
SRC_URI[tfa.sha256sum] = "7c4c00a4f28d3cfbb235fd1a1fb28c4d2fc1d657c9301686e7d8824ef575d059"
SRC_URI[mbedtls.md5sum] = "37cdec398ae9ebdd4640df74af893c95"
SRC_URI[mbedtls.sha256sum] = "a6834fcd7b7e64b83dfaaa6ee695198cb5019a929b2806cb0162e049f98206a4"

require trusted-firmware-a.inc

# The following hack is needed to fit properly in yocto build environment
# TFA is forcing the host compiler and its flags in the Makefile using :=
# assignment for GCC and CFLAGS.
# To properly use the native toolchain of yocto and the right libraries we need
# to pass the proper flags to gcc. This is achieved here by creating a gcc
# script to force passing to gcc the right CFLAGS and LDFLAGS
do_compile_prepend() {
    #Create an host gcc build parser to ensure the proper include path is used
    mkdir -p bin
    echo "#!/usr/bin/env bash" > bin/gcc
    echo "$(which ${BUILD_CC}) ${BUILD_CFLAGS} ${BUILD_LDFLAGS} \$@" >> bin/gcc
    chmod a+x bin/gcc
    export PATH="$PWD/bin:$PATH"
}
