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

# The Arm Compiler is under a EULA, read this at the homepage above and if you
# agree add 'armcompiler' to your LICENSE_FLAGS_WHITELIST.
LICENSE_FLAGS = "armcompiler"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=19faf912b534478d28f60dfa24659c17 \
                    file://license_terms/redistributables.txt;md5=e510e47f7f5be1356ea6218f5b1f6c55 \
                    file://license_terms/supplementary_terms.txt;md5=17a2efdbd320ceda48a3521747e02dd9 \
                    file://license_terms/third_party_licenses.txt;md5=c351a9bed613cf88d4fccd6f0a5e57af "

ARMCLANG_VERSION = "DS500-BN-00026-r5p0-18rel0"

COMPATIBLE_HOST = "x86_64.*-linux"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/compiler/${ARMCLANG_VERSION}.tgz;subdir=${ARMCLANG_VERSION} \
           file://no-uname.patch"
SRC_URI[sha256sum] = "d9fb99e7550366f884c31f74953066da64301fb30601cb55278d738459c22557"

UPSTREAM_CHECK_URI = "https://developer.arm.com/tools-and-software/embedded/arm-compiler/downloads/"
UPSTREAM_CHECK_REGEX = "Download Arm Compiler.*,(?P<pver>[\d\.]+)"

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
