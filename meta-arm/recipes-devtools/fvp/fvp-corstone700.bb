require fvp-ecosystem.inc

MODEL = "Corstone-700"
MODEL_CODE = "FVP_Corstone_700"
PV = "11.22.35"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Corstone-IoT/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "1be7c1b96e086551be18a9998af76877f80bd5ad7fed1976f66a892e8bbdd23c"
SRC_URI[fvp-x86_64.sha256sum] = "0a6f0a4b53ec419dd4c2351b499d7cfbe5c7d52d9ef7df040dfe771d76c58f9e"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=0c32ac6f58ebff83065105042ab98211"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"

