require fvp-ecosystem.inc

MODEL = "RD-V3"
MODEL_CODE = "FVP_RD_V3"
PV = "11.27.51"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Neoverse-Infrastructure/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "e1405fe326cc8956ecb72d0cc421871b83cb9a5ba46cf5665943eef64f8341ca"
SRC_URI[fvp-x86_64.sha256sum] = "d9bd0715de5aa7d69d04239fc2a531c306b656369bb7328427fb6c79a444fab4"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=9ddd501715f7e1fed82c57b260b020ba"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"

require remove-execstack.inc
REMOVE_EXECSTACKS:x86-64 = "${FVPDIR}/models/${FVP_ARCH_DIR}*/libarmctmodel.so"
