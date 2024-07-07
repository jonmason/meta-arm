require fvp-ecosystem.inc

MODEL = "TC2"
MODEL_CODE = "FVP_TC2"
PV = "11.23.28_Linux64"

SRC_URI = "https://developer.arm.com/-/media/Arm%20Developer%20Community/Downloads/OSS/FVP/TotalCompute/${MODEL_CODE}_${PV_URL}.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "321bd1cb32ed98f4256c9c0752a75994e5870e8d376854f85dee3c0bb6918e7f"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=0c32ac6f58ebff83065105042ab98211"
