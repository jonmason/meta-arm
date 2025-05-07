#DEPENDS += "python3-pyelftools-native python3-libclang-native python3-rich"
#DEPENDS += "python3-pyelftools-native python3-libclang-native python3-rich-native"

TFM_PLATFORM = "arm/rse/neoverse_rd/rdv3"
TFM_DEBUG = "1"
EXTRA_OECMAKE += "-DTFM_PLATFORM_VARIANT=0"

SRC_URI_TRUSTED_FIRMWARE_M = "git://gitlab.arm.com/infra-solutions/reference-design/platsw/trusted-firmware-m.git;protocol=https"
SRCBRANCH_tfm = "refinfra"
# use RD-INFRA-2025.07.03
SRCREV_tfm = "2c1ffad021790eca77b7e0105223475441907e87"
SRCREV_mbedtls = "107ea89daaefb9867ea9121002fbbdf926780e98"
SRCREV_tfm-extras = "95add8abb15879f48f1069a0952dd9abdffbc1f8"
SRCREV_tfm-tests = "6f642014a8c255e163ae0bc4d21e327de694d6a2"

#FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
#SRC_URI += "file://0001-initial_attestation-Add-missing-include-for-tfm_strn.patch"
