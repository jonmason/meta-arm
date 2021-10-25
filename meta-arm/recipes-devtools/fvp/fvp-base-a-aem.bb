require fvp-envelope.inc

SUMMARY = "Arm Fixed Virtual Platform - Armv-A Base RevC Architecture Envelope Model FVP"
LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses.txt;md5=72d3e09651c7560595c325ffad728252"

PV = "11.16.16"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/ecosystem-models/${MODEL_CODE}_${PV_URL}.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "a19e18d675b73493b032502fdf6edb7afba01540c99400a4405a95f95009a734"

MODEL_CODE = "FVP_Base_RevC-2xAEMvA"
