require fvp-envelope.inc

SUMMARY = "Arm Fixed Virtual Platform - Armv-A Base RevC Architecture Envelope Model FVP"
LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses.txt;md5=b40ecbbbd3409d48263437b782df6df9"

# This FVP cannot be downloaded directly, so download the Armv-A Base RevC AEM
# FVP yourself from the homepage and set FVP_BASE_A_AEM_TARBALL_URI appropriately
# (for example, file:///home/user/FVP_Base_RevC-2xAEMvA_11.14_21.tgz).
FVP_BASE_A_AEM_TARBALL_URI ?= ""
PV = "11.14_21"

SRC_URI = "${FVP_BASE_A_AEM_TARBALL_URI};subdir=${BP}"
python() {
    if not d.getVar("FVP_BASE_A_AEM_TARBALL_URI"):
        raise bb.parse.SkipRecipe("FVP_BASE_A_AEM_TARBALL_URI not set")
}
