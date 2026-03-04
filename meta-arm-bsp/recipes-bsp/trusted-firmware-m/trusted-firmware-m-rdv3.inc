#DEPENDS += "python3-pyelftools-native python3-libclang-native python3-rich"
#DEPENDS += "python3-pyelftools-native python3-libclang-native python3-rich-native"

TFM_PLATFORM = "arm/rse/neoverse_rd/rdv3"
TFM_DEBUG = "1"
EXTRA_OECMAKE += "-DTFM_PLATFORM_VARIANT=0"

SRC_URI_TRUSTED_FIRMWARE_M = "git://gitlab.arm.com/infra-solutions/reference-design/platsw/trusted-firmware-m.git;protocol=https"
# use RD-INFRA-2025.07.03
SRCBRANCH_tfm = "refinfra"
SRCREV_tfm = "2c1ffad021790eca77b7e0105223475441907e87"
SRCREV_mbedtls = "107ea89daaefb9867ea9121002fbbdf926780e98"
# TF-Mv2.2.2 intermediate SHA from build scripts
SRCBRANCH_tfm-extras = "release/2.2.x"
SRCREV_tfm-extras = "9076ca615da4d8249fb6f1839b1b2c7027be8457"
# TF-Mv2.2.2
#SRCBRANCH_tfm-tests = "release/2.2.x"
#SRCREV_tfm-tests = "e0a433c67c37138cd9dce23657ae82c5cbdcf51f"
#SRCREV_tfm-tests = "6f642014a8c255e163ae0bc4d21e327de694d6a2"
SRCREV_mcuboot = "6071ceb1d0d955b6ff4745499a0ff3ac7d79f24b"
SRCREV_cmsis = "b0bbb0423b278ca632cfe1474eb227961d835fd2"
SRCREV_qcbor = "92d3f89030baff4af7be8396c563e6c8ef263622"
SRCREV_mbedtls = "107ea89daaefb9867ea9121002fbbdf926780e98"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
#SRC_URI += "file://0001-initial_attestation-Add-missing-include-for-tfm_strn.patch"
SRC_URI += "file://0001-Workaround-GCC15-compile-errors.patch"

EXTRA_OECMAKE += "-DCMAKE_C_COMPILER=${BUILD_CC}"
#EXTRA_OECMAKE += "-DRSE_TP_MODE=OFF"
