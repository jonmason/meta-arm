HOMEPAGE = "https://trusted-services.readthedocs.io/en/latest/index.html"

PACKAGE_ARCH = "${MACHINE_ARCH}"

LICENSE = "Apache-2.0 & BSD-3-Clause & Zlib"
LIC_FILES_CHKSUM = "file://license.rst;md5=ea160bac7f690a069c608516b17997f4 \
                    file://mbedcrypto/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
                    file://nanopb/LICENSE.txt;md5=9db4b73a55a3994384112efcdb37c01f \
                    "
SRC_URI = "git://git.trustedfirmware.org/TS/trusted-services.git;protocol=https;branch=main;name=ts;destsuffix=git \
           git://github.com/ARMmbed/mbed-crypto.git;protocol=git;branch=development;name=mbed;destsuffix=git/mbedcrypto \
           git://github.com/nanopb/nanopb.git;name=nanopb;branch=master;destsuffix=git/nanopb \
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

SRCREV_FORMAT = "ts"
SRCREV_ts = "eff4b28b6ae461defb2d8c0f614965439ed19386"
SRCREV_mbed = "cf4a40ba0a3086cabb5a8227245191161fd26383"
SRCREV_nanopb = "df0e92f474f9cca704fe2b31483f0b4d1b1715a4"

S = "${WORKDIR}/git"
TS_DEPLOYMENTS_DIR := "${S}/deployments/"

inherit deploy python3native

DEPENDS = "python3-pycryptodome-native python3-pycryptodomex-native \
           python3-pyelftools-native python3-grpcio-tools-native \
           python3-protobuf-native protobuf-native cmake-native \
           "

# Baremetal, just need a compiler
DEPENDS_remove = "virtual/${TARGET_PREFIX}compilerlibs virtual/libc"

export CROSS_COMPILE = "${TARGET_PREFIX}"

B = "${WORKDIR}/build"

do_configure() {
    cmake \
      -DMBEDCRYPTO_SOURCE_PATH=${S}/mbedcrypto \
      -DNANOPB_SOURCE_PATH=${S}/nanopb \
      -S ${TS_DEPLOYMENT} -B ${B}
}

do_compile() {
    cmake --build ${B}
}

SYSROOT_DIRS = "/firmware"

do_deploy() {
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
addtask deploy after do_install
