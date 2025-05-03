require fvp-ecosystem.inc

MODEL = "Corstone-300"
MODEL_CODE = "FVP_Corstone_SSE-300"
PV = "11.27.42"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Corstone-IoT/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "32a5e84d5f5e39c2832beda5747b2cba0deafee1ac8e3909d7c3fbcad844d031"
SRC_URI[fvp-x86_64.sha256sum] = "6dfba80132b38a6c281948b12724dd0f8568572d56e549c73566275c4f273849"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=91e990146367274ad62761e0753a4846"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"

