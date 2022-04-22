require fvp-envelope.inc

SUMMARY = "Arm Fixed Virtual Platform - Armv8-R Base Architecture Envelope Model FVP"
LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses.txt;md5=41029e71051b1c786bae3112a29905a7"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/ecosystem-models/${MODEL_CODE}_${PV_URL}.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "483ec3c2c6569e3e7e0c4c46329662c0d19475dee8e8947c24fa3de4b00da488"

MODEL_CODE = "FVP_Base_AEMv8R"
