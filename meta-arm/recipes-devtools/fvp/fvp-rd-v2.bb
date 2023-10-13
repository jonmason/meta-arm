require fvp-ecosystem.inc

MODEL = "Neoverse-V2"
MODEL_CODE = "FVP_RD_V2"
PV = "11.20.18"

SRC_URI = "https://developer.arm.com/-/media/Arm%20Developer%20Community/Downloads/OSS/FVP/${MODEL}/RD-V2-11-20-18-release/${MODEL_CODE}_${PV_URL}_Linux64.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "a58bf305373e75e6e8a3163f9bce3818f8cf78f7df96310ff8eafdc2a01f1960"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=34a1ba318d745f05e6197def68ea5411"
