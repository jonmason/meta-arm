# Armv8-A Foundation Platform build recipe

#
# Download and install recipe specific for Armv8-A Foundation Platform build are
# captured in the file.
#

# The tar file required to build this package must be downloaded from
# https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms
# and put in the sub-directory 'licensed/silver.arm.com' of one of the
# following locations:
# - in the directory 'files' of this file directory
# - in your Yocto project download directory (DL_DIR parameter of local.conf)
# - in your Download mirror if you have one
SRC_URI = "file://licensed/silver.arm.com/FM000-KT-00035-${PV}.tgz"
SRC_URI += "file://start-foundation-armv8.sh"

S = "${WORKDIR}/Foundation_Platformpkg"

# Checksums to compare against downloaded package files' checksums
LIC_FILES_CHKSUM = " \
    file://license_terms/license_agreement.txt;md5=ae7b47c67a033995c6b4510476a50f03 \
    file://license_terms/redistributables.txt;md5=f9fafcaf37ce6c9427568b9dbdbaabe5 \
    file://license_terms/supplementary_terms.txt;md5=26e4b214f639a22c8e7e207abc10eccb \
    file://license_terms/third_party_licenses.txt;md5=6394c171d6657fc195573c4d239341c4 \
    "

require fvp-native.inc

do_install_append() {
    cp -a --no-preserve=ownership -rf doc license_terms models plugins \
        ${D}/${datadir}/fvp/.

    cat <<EOF > ${D}${bindir}/Foundation_Platform
#!/bin/bash
basedir=\$(cd \$(dirname \$0)/../../; pwd)
export LD_LIBRARY_PATH="\$basedir/lib:\$basedir/usr/lib"
\$basedir/usr/share/fvp/models/Linux64_GCC-6.4/Foundation_Platform "\$@"
EOF
    chmod 755 ${D}${bindir}/Foundation_Platform
}

do_deploy_append() {
    install -m 755 ${WORKDIR}/start-foundation-armv8.sh ${DEPLOYDIR}/.
}
