require fvp-ecosystem.inc

MODEL = "Corstone-1000"
MODEL_CODE = "FVP_Corstone_1000"
PV = "11.22_35"

SRC_URI = "https://developer.arm.com/-/media/Arm%20Developer%20Community/Downloads/OSS/FVP/${MODEL}/${MODEL_CODE}_${PV}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "40c76551ca73328d34513dbc5de2bd094c28da7e91b73fe0361ec8faef644b68"
SRC_URI[fvp-x86_64.sha256sum] = "30eb648d26827212faeb74b8c10070cbf8bf212d106ee609579f781a32aac6d9"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=0c32ac6f58ebff83065105042ab98211"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"
