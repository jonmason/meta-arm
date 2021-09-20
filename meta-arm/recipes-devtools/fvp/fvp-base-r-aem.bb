require fvp-envelope.inc

SUMMARY = "Arm Fixed Virtual Platform - Armv8-R Base Architecture Envelope Model FVP"
LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses.txt;md5=3db0c4947b7e3405c40b943672d8de2f"

# This FVP cannot be downloaded directly, so download the Armv8-R Base AEM FVP
# yourself from the homepage and set FVP_BASE_R_AEM_TARBALL_URI appropriately
# (for example, file:///home/user/FVP_Base_AEMv8R_11.15_14.tgz).
FVP_BASE_R_AEM_TARBALL_URI ?= ""
PV = "11.15.14"

SRC_URI = "${FVP_BASE_R_AEM_TARBALL_URI};subdir=${BP}"
python() {
    if not d.getVar("FVP_BASE_R_AEM_TARBALL_URI"):
        raise bb.parse.SkipRecipe("FVP_BASE_R_AEM_TARBALL_URI not set")
}
