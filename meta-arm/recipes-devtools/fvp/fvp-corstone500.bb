require fvp-ecosystem.inc

MODEL = "Corstone-500"
MODEL_CODE = "FVP_Corstone_500"
PV = "11.22.35"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Corstone-IoT/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "ce9eead00f641898100d090ed7efc7494b2c7e9a23c1d22ba234e6c4f4da1499"
SRC_URI[fvp-x86_64.sha256sum] = "5f6f0cb6386f3b6a247d21ddfbb901f774013a08a8bf3e97958c00fd8131084b"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=0c32ac6f58ebff83065105042ab98211"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"

