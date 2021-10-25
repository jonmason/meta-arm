require fvp-ecosystem.inc

MODEL = "Library"
MODEL_CODE = "FVP_ARM_Std_Library"
PV = "11.15_14"

HOMEPAGE = "https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=a50d186fffa51ed55599183aad911298 \
                    file://license_terms/third_party_licenses.txt;md5=3db0c4947b7e3405c40b943672d8de2f"


# The FVP Library tarball cannot be downloaded directly, so download the it
# yourself from from the homepage and set FVP_LIBRARY_TARBALL_URI appropriately
# (for example, "file:///home/user/FVP_ARM_Std_Library_11.14_21.tgz").
FVP_LIBRARY_TARBALL_URI ?= ""

SRC_URI = "${FVP_LIBRARY_TARBALL_URI};subdir=${BP}"
python() {
    if not d.getVar("FVP_LIBRARY_TARBALL_URI"):
        raise bb.parse.SkipRecipe("FVP_LIBRARY_TARBALL_URI not set")
}
