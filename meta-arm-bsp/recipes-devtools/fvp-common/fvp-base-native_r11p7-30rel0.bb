# Armv8-A Base Platform FVP build recipe

#
# Download and install recipe specific for Armv8-A Base Platform FVP build are
# captured in the file.
#

# The tar file required to build this package must be downloaded from
# https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms
# and put in the sub-directory 'licensed/silver.arm.com' of one of the
# following locations:
# - in the directory 'files' of this file directory
# - in your Yocto project download directory (DL_DIR parameter of local.conf)
# - in your Download mirror if you have one
SRC_URI = "file://licensed/silver.arm.com/FM000-KT-00173-${PV}.tgz"
SRC_URI += "file://start-fvp-base.sh"

S = "${WORKDIR}/Base_RevC_AEMv8A_pkg"

# Checksums to compare against downloaded package files' checksums
LIC_FILES_CHKSUM = " \
    file://license_terms/license_agreement.txt;md5=ae7b47c67a033995c6b4510476a50f03 \
    file://license_terms/redistributables.txt;md5=f9fafcaf37ce6c9427568b9dbdbaabe5 \
    file://license_terms/supplementary_terms.txt;md5=26e4b214f639a22c8e7e207abc10eccb \
    file://license_terms/third_party_licenses.txt;md5=1aa4ab9ee0642b1bc92063d29426c25f \
    "

require fvp-native.inc

do_install_append() {
    cp -a --no-preserve=ownership -rf bin doc fmtplib license_terms models \
        plugins scripts ${D}/${datadir}/fvp/.

    cat <<EOF > ${D}${bindir}/FVP_Base_RevC-2xAEMv8A
#!/bin/bash
basedir=\$(cd \$(dirname \$0)/../../; pwd)
export LD_LIBRARY_PATH="\$basedir/lib:\$basedir/usr/lib"
\$basedir/usr/share/fvp/models/Linux64_GCC-4.9/FVP_Base_RevC-2xAEMv8A "\$@"
EOF
    chmod 755 ${D}${bindir}/FVP_Base_RevC-2xAEMv8A
}

do_deploy_append() {
    install -m 755 ${WORKDIR}/start-fvp-base.sh ${DEPLOYDIR}/.
}
