SUMMARY = "Mbedcrypto for trusted services"
DESCRIPTION = "A reference implementation of the cryptography \
interface of the Arm Platform Security Architecture (PSA). Compiled \
with the configuration for trusted services."
HOMEPAGE = "https://github.com/ARMmbed/mbed-crypto"

LICENSE = "Apache-2.0 & BSD-3-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=302d50a6369f5f22efdb674db908167a \
                    file://ts/license.rst;md5=ea160bac7f690a069c608516b17997f4 \
                    "
SRC_URI = "git://github.com/ARMmbed/mbed-crypto.git;protocol=git;branch=development;name=mbed;destsuffix=git \
           git://git.trustedfirmware.org/TS/trusted-services.git;protocol=https;branch=main;name=ts;destsuffix=git/ts \
           file://0001-Add-a-new-environment-to-run-TS-with-a-shim-layer-in.patch;patchdir=${S}/ts \
           file://0002-Change-instruction-access-permissions-of-shared-memo.patch;patchdir=${S}/ts \
           file://0003-Set-in_region_count-to-0-during-memory-retrieve.patch;patchdir=${S}/ts \
           file://0004-Release-rx-buffer-after-memory-retrieve-request.patch;patchdir=${S}/ts \
           file://0005-crypto-sp-Create-a-new-deployment-with-the-shim-envi.patch;patchdir=${S}/ts \
           file://0006-secure-storage-Create-a-new-deployment-with-the-shim.patch;patchdir=${S}/ts \
           file://0007-crypto-shim-Don-t-link-against-unrequired-libraries.patch;patchdir=${S}/ts \
           file://0008-libts-arm-linux-Add-version-to-libts.so.patch;patchdir=${S}/ts \
           file://0009-libts-Add-option-to-use-installed-libts.patch;patchdir=${S}/ts \
           file://0010-external-Add-option-to-use-local-source-or-installed.patch;patchdir=${S}/ts \
           file://0011-aarch64-Allow-the-stack-to-be-further-than-1MB-from-.patch;patchdir=${S}/ts \
           file://0012-libc-Add-missing-libc-function-declarations.patch;patchdir=${S}/ts \
           file://0013-libsp-modify-FFA-ABIs-with-supported-convention.patch;patchdir=${S}/ts \
           "

PV = "3.1.0+git"

SRCREV_FORMAT = "mbed"
SRCREV_mbed = "cf4a40ba0a3086cabb5a8227245191161fd26383"
SRCREV_ts = "eff4b28b6ae461defb2d8c0f614965439ed19386"

S = "${WORKDIR}/git"

inherit cmake

MBEDCRYPTO_CONFIG_FILE = "${S}/ts/components/service/crypto/client/cpp/config_mbed_crypto.h"

OECMAKE_GENERATOR = "Unix Makefiles"
EXTRA_OECMAKE = "-DCMAKE_POSITION_INDEPENDENT_CODE=True \
                 -DENABLE_PROGRAMS=OFF \
                 -DENABLE_TESTING=OFF \
                 -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
                 -Dthirdparty_def=-DMBEDTLS_CONFIG_FILE=\"${MBEDCRYPTO_CONFIG_FILE}\" \
                 "
