require fvp-ecosystem.inc

MODEL = "Corstone-1000"
MODEL:cortexa320 = "Corstone-1000-with-Cortex-A320"
MODEL_CODE = "FVP_Corstone_1000"
MODEL_CODE:cortexa320 = "FVP_Corstone_1000-A320"
PV = "11.23.25"
PV:cortexa320 = "11.30.27"

FVP_AARCH64_SHA256SUM = "e299e81d5fa8b3d2afee0850fd03be31c1a1c3fad07f79849c63e46ee5e36acc"
FVP_AARCH64_SHA256SUM:cortexa320 = "a45898fead5549779153263c3544fa1032c285d532275eb678f58cae3317b01f"
FVP_X86_64_SHA256SUM = "ec34c9564ccb5b1eb62fc2757673343a353db1d116a7cb1b5f82f9d985d99cdf"
FVP_X86_64_SHA256SUM:cortexa320 = "d57b248a1c1bc5a6040605d50af94a5151adc4da26ec9acc456ec86b819ffb76"

SRC_URI = "https://developer.arm.com/-/cdn-downloads/permalink/FVPs-Corstone-IoT/${MODEL}/${MODEL_CODE}_${PV_URL}_${FVP_ARCH}.tgz;subdir=${BP};name=fvp-${HOST_ARCH}"
SRC_URI[fvp-aarch64.sha256sum] = "${FVP_AARCH64_SHA256SUM}"
SRC_URI[fvp-x86_64.sha256sum] = "${FVP_X86_64_SHA256SUM}"


# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

LIC_FILES_CHKSUM_MD5 = "0c32ac6f58ebff83065105042ab98211"
LIC_FILES_CHKSUM_MD5:cortexa320 = "a5ce56e117d0ab63791fbb7c35ec2211"

LIC_FILES_CHKSUM = "\
    file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=${LIC_FILES_CHKSUM_MD5} \
"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"
