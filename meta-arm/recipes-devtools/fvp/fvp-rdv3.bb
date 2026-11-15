require fvp-ecosystem.inc

MODEL = "RD-V3"
MODEL_CODE = "FVP_RD_V3"
PV = "11.29.35"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Neoverse-Infrastructure/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "d129dffff1d075d5620d63e83f31fd01e7b5a0b32c1507109533f2f057f6960f"
SRC_URI[fvp-x86_64.sha256sum] = "76ed73a5362c2d5e3ad5e2b4bbf691ba2f21373decae2a2223f479b4d0dad5dc"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=41f1533ebfbd4f1d32cfc82b55f6729a"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"

require remove-execstack.inc
REMOVE_EXECSTACKS:x86-64 = "${FVPDIR}/models/${FVP_ARCH_DIR}*/libarmctmodel.so"
