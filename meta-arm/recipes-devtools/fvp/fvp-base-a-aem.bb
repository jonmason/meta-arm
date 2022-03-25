require fvp-envelope.inc

SUMMARY = "Arm Fixed Virtual Platform - Armv-A Base RevC Architecture Envelope Model FVP"
LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses.txt;md5=41029e71051b1c786bae3112a29905a7"

PV = "11.17.21"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/ecosystem-models/${MODEL_CODE}_${PV_URL}.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "ef42f685b4b970e56f6b14a5a76acb4eb88987dcb614d5788eee4d8ef5cf9b28"

MODEL_CODE = "FVP_Base_RevC-2xAEMvA"
