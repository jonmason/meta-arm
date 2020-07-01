# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020 Arm Limited
#

SUMMARY = "Trusted Firmware for Cortex-M"
DESCRIPTION = "Trusted Firmware-M"
HOMEPAGE = "https://git.trustedfirmware.org/trusted-firmware-m.git"
PROVIDES = "virtual/trusted-firmware-m"

# TF-Mv1.0
SRCREV_tfm = "TF-Mv1.0"
LICENSE = "BSD-3-Clause & Apachev2"

LIC_FILES_CHKSUM ?= "file://license.rst;md5=07f368487da347f3c7bd0fc3085f3afa"
LIC_FILES_CHKSUM += "file://../mbed-crypto/LICENSE;md5=302d50a6369f5f22efdb674db908167a"
LIC_FILES_CHKSUM += "file://../mbedtls/LICENSE;md5=302d50a6369f5f22efdb674db908167a"
LIC_FILES_CHKSUM += "file://../CMSIS_5/LICENSE.txt;md5=c4082b6c254c9fb71136710391d9728b"

SRC_URI  = "git://git.trustedfirmware.org/trusted-firmware-m.git;protocol=https;branch=master;name=tfm;destsuffix=${S}"
SRC_URI += "git://github.com/ARMmbed/mbed-crypto.git;protocol=https;branch=development;name=mbed-crypto;destsuffix=${S}/../mbed-crypto"
SRC_URI += "git://github.com/ARMmbed/mbedtls.git;protocol=https;branch=mbedtls-2.7;name=mbedtls;destsuffix=${S}/../mbedtls"
SRC_URI += "https://github.com/ARM-software/CMSIS_5/releases/download/5.5.0/ARM.CMSIS.5.5.0.pack;name=cmsis;subdir=${S}/../CMSIS_5;downloadfilename=ARM.CMSIS.5.5.0.zip"

SRC_URI[cmsis.md5sum] = "73b6cf6b4ab06ac099478e6cf983c08e"
SRC_URI[cmsis.sha256sum] = "fc6e46c77de29ed05ef3bfd4846a2da49b024bc8854c876ac053aaa8d348ac52"

SRCREV_FORMAT ?= "tfm_mbed-crypto_mbedtls_cmsis"
SRCREV_mbed-crypto ?= "mbedcrypto-3.0.1"
SRCREV_mbedtls ?= "mbedtls-2.7.14"
SRCREV_cmsis ?= "5.5.0"

inherit python3native deploy

TFM_DEPENDS ?= ""
DEPENDS += "${TFM_DEPENDS}"
DEPENDS += "cmake-native"
DEPENDS += "python3-cryptography-native python3-pyasn1-native"
DEPENDS += "python3-jinja2-native python3-cbor-native python3-pyyaml-native"

S = "${WORKDIR}/git/tfm"
B = "${S}/build"

COMPATIBLE_MACHINE ?= "invalid"

# Build for debug (set TFA_DEBUG to 1 to activate)
TFM_DEBUG ?= "0"
# Set target config
TFM_CONFIG ?= "ConfigDefault.cmake"
# Platform must be set for each machine
TFM_PLATFORM ?= "invalid"

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

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

# This is needed because CMSIS_5 source package originally has .pack extension not .zip
# and bitbake checks this dependency based on file extension
do_unpack[depends] += "unzip-native:do_populate_sysroot"

do_configure[prefuncs] += "do_check_config"
do_check_config() {
    if [ ! -f "${S}/configs/${TFM_CONFIG}" ]; then
        bbfatal "Couldn't find config file '${TFM_CONFIG}' in '${S}/configs/'"
    fi
}

do_configure() {
    cd ${S}
    python3 "tools/tfm_parse_manifest_list.py"

    if [ ! -d "${B}" ]
    then
        install -d ${B}
    else
        rm -f ${B}/CMakeCache.txt
    fi

    cd ${B}
    cmake -G"Unix Makefiles" --build ${S} ${EXTRA_OECMAKE}
}

do_compile() {
    if [ -d "${B}" ]
    then
        oe_runmake -C ${B} install
    else
        bbfatal "TF-M CMake not generated!"
    fi
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
