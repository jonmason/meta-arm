# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020 Arm Limited
#

SUMMARY = "Trusted Firmware for Cortex-M"
DESCRIPTION = "Trusted Firmware-M"
HOMEPAGE = "https://git.trustedfirmware.org/trusted-firmware-m.git"
PROVIDES = "virtual/trusted-firmware-m"

LICENSE = "BSD-3-Clause & Apachev2"

LIC_FILES_CHKSUM = "file://license.rst;md5=07f368487da347f3c7bd0fc3085f3afa \
                    file://../tf-m-tests/license.rst;md5=02d06ffb8d9f099ff4961c0cb0183a18 \
                    file://../mbedtls/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57 \
                    file://../mcuboot/LICENSE;md5=b6ee33f1d12a5e6ee3de1e82fb51eeb8"

SRC_URI  = "git://git.trustedfirmware.org/TF-M/trusted-firmware-m.git;protocol=https;branch=master;name=tfm;destsuffix=${S} \
            git://git.trustedfirmware.org/TF-M/tf-m-tests.git;protocol=https;branch=master;name=tfm-tests;destsuffix=${S}/../tf-m-tests \
            git://github.com/ARMmbed/mbedtls.git;protocol=https;branch=master;name=mbedtls;destsuffix=${S}/../mbedtls \
            git://github.com/mcu-tools/mcuboot.git;protocol=https;branch=v1.7-branch;name=mcuboot;destsuffix=${S}/../mcuboot \
            "

# The required dependencies are documented in tf-m/config/config_default.cmake
# TF-Mv1.3.0
SRCREV_tfm = "aa7d90a23b045e50c26ef66b11250842b665f54b"
# mbedtls 2.26
SRCREV_mbedtls = "e483a77c85e1f9c1dd2eb1c5a8f552d2617fe400"
# tf-m-tests v1.3.0
SRCREV_tfm-tests = "e7430d13b388a106c9f4cfb534e7340ce1482575"
# 1.7.2
SRCREV_mcuboot = "4aa516e7281fc6f9a2dce0b0efda9acc580fa254"

UPSTREAM_CHECK_GITTAGREGEX = "^TF-Mv(?P<pver>\d+(\.\d+)+)$"

# Note to future readers of this recipe: until the CMakeLists don't abuse
# installation (see do_install) there is no point in trying to inherit
# cmake here. You can easily short-circuit the toolchain but the install
# is so convoluted there's no gain.

inherit python3native deploy

# Baremetal and we bring a compiler below
INHIBIT_DEFAULT_DEPS = "1"

PACKAGE_ARCH = "${MACHINE_ARCH}"

DEPENDS += "cmake-native \
            python3-intelhex-native \
            python3-jinja2-native \
            python3-pyyaml-native \
            python3-click-native \
            python3-cryptography-native \
            python3-pyasn1-native \
            python3-cbor-native"

S = "${WORKDIR}/git/tfm"
B = "${WORKDIR}/build"

# Build for debug (set TFM_DEBUG to 1 to activate)
TFM_DEBUG ?= "0"

# Platform must be set, ideally in the machine configuration.
TFM_PLATFORM ?= ""
python() {
    if not d.getVar("TFM_PLATFORM"):
        raise bb.parse.SkipRecipe("TFM_PLATFORM needs to be set")
}

PACKAGECONFIG ??= "cc-gnuarm"
# What compiler to use
PACKAGECONFIG[cc-gnuarm] = "-DTFM_TOOLCHAIN_FILE=${S}/toolchain_GNUARM.cmake,,gcc-arm-none-eabi-native"
PACKAGECONFIG[cc-armclang] = "-DTFM_TOOLCHAIN_FILE=${S}/toolchain_ARMCLANG.cmake,,armcompiler-native"
# Whether to integrate the test suite
PACKAGECONFIG[test-secure] = "-DTEST_S=ON,-DTEST_S=OFF"
PACKAGECONFIG[test-nonsecure] = "-DTEST_NS=ON,-DTEST_NS=OFF"

# Add platform parameters
EXTRA_OECMAKE += "-DTFM_PLATFORM=${TFM_PLATFORM}"

# Handle TFM_DEBUG parameter
EXTRA_OECMAKE += "${@bb.utils.contains('TFM_DEBUG', '1', '-DCMAKE_BUILD_TYPE=Debug', '', d)}"

# Verbose builds
EXTRA_OECMAKE += "-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON"

EXTRA_OECMAKE += "-DMBEDCRYPTO_PATH=${S}/../mbedtls -DTFM_TEST_REPO_PATH=${S}/../tf-m-tests -DMCUBOOT_PATH=${S}/../mcuboot"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

# TF-M ships patches that it needs applied to mbedcrypto, so apply them
# as part of do_patch.
apply_local_patches() {
    cat ${S}/lib/ext/mbedcrypto/*.patch | patch -p1 -d ${S}/../mbedtls
}
do_patch[postfuncs] += "apply_local_patches"

do_configure[cleandirs] = "${B}"
do_configure() {
    cmake -G"Unix Makefiles" -S ${S} -B ${B} ${EXTRA_OECMAKE} ${PACKAGECONFIG_CONFARGS}
}

# Invoke install here as there's no point in splitting compile from install: the
# first thing the build does is 'install' inside the build tree thus causing a
# rebuild. It also overrides the install prefix to be in the build tree, so you
# can't use the usual install prefix variables.
do_compile() {
    cmake --build ${B} -- install
}

do_install() {
    # TODO install headers and static libraries when we know how they're used
    install -d -m 755 ${D}/firmware
    install -m 0644 ${B}/bin/* ${D}/firmware/
}

FILES:${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"

addtask deploy after do_install
do_deploy() {
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
