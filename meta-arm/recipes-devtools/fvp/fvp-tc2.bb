require fvp-ecosystem.inc

MODEL = "TC2"
MODEL_CODE = "FVP_TC2"
PV = "11.22.34_Linux64"

SRC_URI = "https://developer.arm.com/-/media/Arm%20Developer%20Community/Downloads/OSS/FVP/TotalCompute/${MODEL_CODE}_${PV_URL}.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "11dd8817c4a7b6f2d9b720c3beed71762a1c5d49331f3e424a6326a837537af0"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=0c32ac6f58ebff83065105042ab98211"
