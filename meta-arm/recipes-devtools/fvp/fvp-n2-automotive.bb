require fvp-ecosystem.inc

MODEL = "Neoverse N2 Automotive"
MODEL_CODE = "FVP_RD_N2_Automotive"
PV = "11.20.20"

SRC_URI = "https://developer.arm.com/-/media/Arm%20Developer%20Community/Downloads/OSS/FVP/Automotive%20FVPs/${MODEL_CODE}_${PV_URL}_Linux64.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "20c809defe115bff0aa821baca144b074bb4548da56ccba542405abb0f5e5d36"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=34a1ba318d745f05e6197def68ea5411"
