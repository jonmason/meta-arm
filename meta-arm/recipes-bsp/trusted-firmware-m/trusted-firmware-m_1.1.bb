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
                    file://../mbed-crypto/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
                    file://../mcuboot/LICENSE;md5=b6ee33f1d12a5e6ee3de1e82fb51eeb8"

SRC_URI  = "git://git.trustedfirmware.org/TF-M/trusted-firmware-m.git;protocol=https;branch=master;name=tfm;destsuffix=${S} \
            git://git.trustedfirmware.org/TF-M/tf-m-tests.git;protocol=https;branch=master;name=tfm-tests;destsuffix=${S}/../tf-m-tests \
            git://github.com/ARMmbed/mbed-crypto.git;protocol=https;branch=development;name=mbed-crypto;destsuffix=${S}/../mbed-crypto \
            git://github.com/JuulLabs-OSS/mcuboot.git;protocol=https;name=mcuboot;destsuffix=${S}/../mcuboot \
            file://objcopy.patch"

# TF-Mv1.1
SRCREV_tfm = "a6b336c1509fd5f5522450e3cec0fcd6c060f9c8"
# mbedcrypto-3.0.1
SRCREV_mbed-crypto = "1146b4e06011b69a6437e6b728f2af043a06ec19"
# TF-Mv1.1
SRCREV_tfm-tests = "5a571808e7841f15cc966661a64dd6adb3b40f6c"
# v1.6.0
SRCREV_mcuboot = "50d24a57516f558dac72bef634723b60c5cfb46b"

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
            python3-cryptography-native \
            python3-pyasn1-native \
            python3-cbor-native"

S = "${WORKDIR}/git/tfm"
B = "${WORKDIR}/build"

# Build for debug (set TFA_DEBUG to 1 to activate)
TFM_DEBUG ?= "0"
# Set target config
TFM_CONFIG ?= "ConfigDefault.cmake"

# Platform must be set, ideally in the machine configuration.
TFM_PLATFORM ?= ""
python() {
    if not d.getVar("TFM_PLATFORM"):
        raise bb.parse.SkipRecipe("TFM_PLATFORM needs to be set")
}

# Uncomment, or copy these lines to your local.conf to use the Arm Clang compiler
# from meta-arm-toolchain.
# Please make sure to check the applicable license beforehand!
#LICENSE_FLAGS_WHITELIST = "armcompiler_armcompiler-native"
#TFM_COMPILER = "ARMCLANG"
# For most targets, it is required to set and export the following LICENSE variables for the armcompiler:
# ARM_TOOL_VARIANT, ARMLMD_LICENSE_FILE, LM_LICENSE_FILE

# Setting GCC as the default TF-M compiler
TFM_COMPILER ?= "GNUARM"
DEPENDS += "${@'armcompiler-native' if d.getVar('TFM_COMPILER', True) == 'ARMCLANG' else 'gcc-arm-none-eabi-native'}"

# Add platform parameters
EXTRA_OECMAKE += "-DTARGET_PLATFORM=${TFM_PLATFORM}"

# Add compiler parameters
EXTRA_OECMAKE += "-DCOMPILER=${TFM_COMPILER}"

# Handle TFM_DEBUG parameter
EXTRA_OECMAKE += "${@bb.utils.contains('TFM_DEBUG', '1', '-DCMAKE_BUILD_TYPE=Debug', '', d)}"
EXTRA_OECMAKE += "-DPROJ_CONFIG=${S}/configs/${TFM_CONFIG}"

# Verbose builds
EXTRA_OECMAKE += "-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

do_configure[prefuncs] += "do_check_config"
do_check_config() {
    if [ ! -f "${S}/configs/${TFM_CONFIG}" ]; then
        bbfatal "Couldn't find config file '${TFM_CONFIG}' in '${S}/configs/'"
    fi
}

do_configure[cleandirs] = "${B}"
do_configure() {
    cmake -G"Unix Makefiles" ${S} ${EXTRA_OECMAKE}
}

# Invoke install here as there's no point in splitting compile from install: the
# first thing the build does is 'install' inside the build tree thus causing a
# rebuild. It also overrides the install prefix to be in the build tree, so you
# can't use the usual install prefix variables.
do_compile() {
    cmake --build ./ -- install
}

do_install() {
    if [ ! -d "${B}/install/outputs" ]
    then
        bbfatal "Output not found in '${B}/install/outputs'!"
    fi

    install -d -m 755 ${D}/firmware
    cd ${B}/install/outputs
    for dir in *;do
        install -D -p -m 0644 $dir/* -t ${D}/firmware/$dir/
    done
}

FILES_${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"
# Skip QA check for relocations in .text of elf binaries
INSANE_SKIP_${PN} = "textrel"

addtask deploy after do_install
do_deploy() {
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
