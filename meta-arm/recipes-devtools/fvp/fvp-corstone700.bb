require fvp-ecosystem.inc

MODEL = "Corstone-700"
MODEL_CODE = "FVP_Corstone_700"
PV = "11.10.47"

SRC_URI = "https://developer.arm.com/-/media/Arm%20Developer%20Community/Downloads/OSS/FVP/${MODEL}/${MODEL}-updated-11-10-47/${MODEL_CODE}_${PV_URL}.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "255207771864edeca2610958811d30e458c03a2db01950355a455513bad782ec"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses.txt;md5=47473b1e04b70938cf0a7ffea8ea4cc3"
