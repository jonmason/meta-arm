SUMMARY = "Trusted Services demo application"
HOMEPAGE = "https://trusted-services.readthedocs.io/en/latest/index.html"

LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://license.rst;md5=ea160bac7f690a069c608516b17997f4"

SRC_URI = "git://git.trustedfirmware.org/TS/trusted-services.git;protocol=https;branch=main \
           file://0001-Add-a-new-environment-to-run-TS-with-a-shim-layer-in.patch \
           file://0002-Change-instruction-access-permissions-of-shared-memo.patch \
           file://0003-Set-in_region_count-to-0-during-memory-retrieve.patch \
           file://0004-Release-rx-buffer-after-memory-retrieve-request.patch \
           file://0005-crypto-sp-Create-a-new-deployment-with-the-shim-envi.patch \
           file://0006-secure-storage-Create-a-new-deployment-with-the-shim.patch \
           file://0007-crypto-shim-Don-t-link-against-unrequired-libraries.patch \
           file://0008-libts-arm-linux-Add-version-to-libts.so.patch \
           file://0009-libts-Add-option-to-use-installed-libts.patch \
           file://0010-external-Add-option-to-use-local-source-or-installed.patch \
           file://0011-aarch64-Allow-the-stack-to-be-further-than-1MB-from-.patch \
           file://0012-libc-Add-missing-libc-function-declarations.patch \
           file://0013-libsp-modify-FFA-ABIs-with-supported-convention.patch \
          "

PV = "1.0+git${SRCPV}"
SRCREV = "eff4b28b6ae461defb2d8c0f614965439ed19386"

S = "${WORKDIR}/git"

inherit deploy python3native cmake

DEPENDS = "python3-pycryptodome-native python3-pycryptodomex-native \
           python3-pyelftools-native python3-grpcio-tools-native \
           python3-protobuf-native protobuf-native nanopb nanopb-native \
           ts-mbedcrypto libts ts-cpputest"

OECMAKE_SOURCEPATH = "${S}/deployments/ts-service-test/arm-linux"
OECMAKE_GENERATOR = "Unix Makefiles"
EXTRA_OECMAKE = "-DCMAKE_POSITION_INDEPENDENT_CODE=True \
                 -DMBEDCRYPTO_USE_INSTALLED=True \
                 -DNANOPB_USE_INSTALLED=True \
                 -DLIBTS_USE_INSTALLED=True \
                 -DCPPUTEST_USE_INSTALLED=True \
                "
