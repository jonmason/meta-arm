require fvp-ecosystem.inc

MODEL = "Corstone-320"
MODEL_CODE = "FVP_Corstone_SSE-320"
PV = "11.27.25"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Corstone-IoT/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "6766fd2ba138473c6b01c7e2f98125439ba68b638a08c6d11e3e1aeffb88878a"
SRC_URI[fvp-x86_64.sha256sum] = "6986af8805de54fa8dcbc54ea2cd63b305ebf5f1c07d3cba09641e2f8cc4e2f5"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=a3ce84371977a6b9c624408238309a90"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"

