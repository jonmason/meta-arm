# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020 Arm Limited
#

require arm-binary-toolchain.inc

SUMMARY = "Baremetal Armcompiler for Cortex-A, Cortex-R and Cortex-M processors"
HOMEPAGE = "https://developer.arm.com/tools-and-software/embedded/arm-compiler/downloads/version-6"

# Certain features of armcompiler requires a license. For more information, please refer to the armcompiler user guide:
# https://developer.arm.com/tools-and-software/software-development-tools/license-management/resources/product-and-toolkit-configuration
# Usually set and export of these variables are required:
# ARM_TOOL_VARIANT, ARMLMD_LICENSE_FILE, LM_LICENSE_FILE

LICENSE = "Armcompiler-License-agreement & Armcompiler-Redistributables & \
           Armcompiler-Supplementary-terms & Armcompiler-Third-party-licenses"
LICENSE_FLAGS = "armcompiler"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=40cd57dbb1f9d111fb6923945849d51c \
                    file://license_terms/redistributables.txt;md5=e510e47f7f5be1356ea6218f5b1f6c55 \
                    file://license_terms/supplementary_terms.txt;md5=17a2efdbd320ceda48a3521747e02dd9 \
                    file://license_terms/third_party_licenses.txt;md5=6273fa29eb26c0093e1a7deaef7bafec "

PROVIDES = "virtual/armcompiler"

ARMCLANG_VERSION = "DS500-BN-00026-r5p0-15rel0"

COMPATIBLE_HOST = "x86_64.*-linux"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/compiler/${ARMCLANG_VERSION}.tgz;subdir=${ARMCLANG_VERSION}"

SRC_URI[md5sum] = "fbed6edf5eb211c45df7b8548a10535a"
SRC_URI[sha256sum] = "de3947525d9846a09cca52cfa84eb880e73f04398b778e4e599366d4c2416596"

S = "${WORKDIR}/${ARMCLANG_VERSION}"

do_install() {
    install -d ${D}${datadir}/armclang/
    # Commercial license flag set, so recipe will only install when explicitly agreed to it already
    ${S}/install_x86_64.sh --i-agree-to-the-contained-eula -d ${D}${datadir}/armclang/ --no-interactive

    install -d ${D}${bindir}
    # Symlink all executables into bindir
    for f in ${D}${datadir}/armclang/bin/*; do
        lnr $f ${D}${bindir}/$(basename $f)
    done
}
