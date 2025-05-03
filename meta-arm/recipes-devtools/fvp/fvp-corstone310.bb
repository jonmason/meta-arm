require fvp-ecosystem.inc

MODEL = "Corstone-310"
MODEL_CODE = "FVP_Corstone_SSE-310"
PV = "11.27.42"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Corstone-IoT/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "cc4f8b4dd6c2b0e28deaccd600cfdb35edd6a31cb309955eb091a40d0be6226f"
SRC_URI[fvp-x86_64.sha256sum] = "3d31d2a26a2ea76393335927f6b12a317b6bdab0a3d5198530e73fa04fea713c"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=91e990146367274ad62761e0753a4846"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"

