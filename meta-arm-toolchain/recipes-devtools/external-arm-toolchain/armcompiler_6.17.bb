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

NO_GENERIC_LICENSE[Armcompiler-License-agreement] = "license_terms/license_agreement.txt"
NO_GENERIC_LICENSE[Armcompiler-Redistributables] = "license_terms/redistributables.txt"
NO_GENERIC_LICENSE[Armcompiler-Supplementary-terms] = "license_terms/supplementary_terms.txt"
NO_GENERIC_LICENSE[Armcompiler-Third-party-licenses] = "license_terms/third_party_licenses.txt"

# The Arm Compiler is under a EULA, read this at the homepage above and if you
# agree add 'armcompiler' to your LICENSE_FLAGS_ACCEPTED.
LICENSE_FLAGS = "armcompiler"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=19faf912b534478d28f60dfa24659c17 \
                    file://license_terms/redistributables.txt;md5=c22d8d2388d8e592f4b135f87bb243da \
                    file://license_terms/supplementary_terms.txt;md5=e2443a4a7c520e79ebb603c8ba509076 \
                    file://license_terms/third_party_licenses.txt;md5=53b42e7d31259bdc174b9c03651ed1b7 "

ARMCLANG_VERSION = "DS500-BN-00026-r5p0-19rel0"

COMPATIBLE_HOST = "x86_64.*-linux"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/compiler/${ARMCLANG_VERSION}.tgz;subdir=${ARMCLANG_VERSION} \
           file://no-uname.patch"
SRC_URI[sha256sum] = "0ed2c3a2e416f07b892250fcbcca4b27353b046a030a433bf6dddc0db802885c"

UPSTREAM_CHECK_URI = "https://developer.arm.com/tools-and-software/embedded/arm-compiler/downloads/"
UPSTREAM_CHECK_REGEX = "Download Arm Compiler.*,(?P<pver>[\d\.]+)"

S = "${WORKDIR}/${ARMCLANG_VERSION}"

do_install() {
    install -d ${D}${bindir} ${D}${libexecdir}/${BPN}/
    # Commercial license flag set, so recipe will only install when explicitly agreed to it already
    ${S}/install_x86_64.sh --i-agree-to-the-contained-eula -d ${D}${libexecdir}/${BPN}/ --no-interactive

    # Symlink all executables into bindir
    for f in ${D}${libexecdir}/${BPN}/bin/*; do
        ln -rs $f ${D}${bindir}/$(basename $f)
    done
}
