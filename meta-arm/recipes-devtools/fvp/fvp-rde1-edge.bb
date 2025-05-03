require fvp-ecosystem.inc

MODEL = "RD-E1_Edge"
MODEL_CODE = "FVP_RD_E1_edge"
PV = "11.22.17"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Neoverse-Infrastructure/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-x86_64.sha256sum] = "5c4e66e36f6d8f165f9ce61254cbe1daa013e1a9ef09ca59f0bd9cb1b31c6cc6"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=34a1ba318d745f05e6197def68ea5411"
