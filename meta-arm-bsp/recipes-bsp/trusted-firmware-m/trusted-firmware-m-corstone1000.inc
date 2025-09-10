# Corstone1000 machines specific TFM support

COMPATIBLE_MACHINE = "(corstone1000)"

TFM_PLATFORM = "arm/corstone1000"

TFM_DEBUG = "1"

# These dependencies are needed for TF-M v2.2.0 and above
# https://github.com/TrustedFirmware-M/trusted-firmware-m/blob/TF-Mv2.2.0/tools/requirements.txt
DEPENDS:append = " clang-native python3-rich-native python3-pyelftools-native"

## Default is the MPS3 board
TFM_PLATFORM_IS_FVP ?= "FALSE"
EXTRA_OECMAKE += "-DPLATFORM_IS_FVP=${TFM_PLATFORM_IS_FVP}"
EXTRA_OECMAKE += "-DCC312_LEGACY_DRIVER_API_ENABLED=OFF"
EXTRA_OECMAKE:append:corstone1000-fvp = " -DENABLE_MULTICORE=${@bb.utils.contains('MACHINE_FEATURES', 'corstone1000_fvp_smp', 'TRUE', 'FALSE', d)}"
EXTRA_OECMAKE:append:corstone1000-mps3 = " -DPLATFORM_PSA_ADAC_SECURE_DEBUG=${@bb.utils.contains('MACHINE_FEATURES', 'secure-debug', 'ON', 'OFF', d)}"
EXTRA_OECMAKE:append:corstone1000-mps3 = " -DPLATFORM_PSA_ADAC_SOURCE_PATH=${S}/../tfm-psa-adac -DPLATFORM_PSA_ADAC_BUILD_PATH=${B}/tfm-psa-adac-build"

SRC_URI += " \
            file://0001-arm-trusted-firmware-m-disable-address-warnings-into.patch \
           "

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append:corstone1000 = " \
    file://0001-Platform-CS1000-Remove-unused-BL1-files.patch \
    file://0002-Platform-Corstone1000-Fix-BL1-compiler-switch-and-re.patch \
    file://0003-CC312-alignment-of-cc312-differences-between-fvp-and.patch \
    file://0004-Platform-Corstone1000-Enable-FWU-partition.patch \
    file://0005-Platform-Corstone1000-Implement-Bootloader-Abstracti.patch \
    file://0006-Platform-Corstone1000-Increase-buffer-sizes.patch \
    file://0007-Platform-Corstone1000-Remove-duplicate-configuration.patch \
    file://0008-Platform-Corstone1000-Increase-BL1-size-and-align-bi.patch \
    file://0009-Platform-CS1K-Adapt-ADAC-enabled-build-to-the-new-BL.patch \
    "

FILESEXTRAPATHS:prepend:corstone1000-mps3 := "${THISDIR}/files/corstone1000/psa-adac:"
SRC_URI:append:corstone1000-mps3 = " \
    file://0001-PSA-revert-header-versions.patch;patchdir=../tfm-psa-adac \
    file://0002-ADAC-Link-psa_interface-instead-of-tfm_sprt.patch;patchdir=../tfm-psa-adac \
    file://0003-Fix-psa_key_handle_t-initialization.patch;patchdir=../tfm-psa-adac \
    "

do_install() {
  install -D -p -m 0644 ${B}/bin/tfm_s_signed.bin ${D}/firmware/tfm_s_signed.bin
  install -D -p -m 0644 ${B}/bin/bl2_signed.bin ${D}/firmware/bl2_signed.bin
  install -D -p -m 0644 ${B}/bin/bl1_1.bin ${D}/firmware/bl1_1.bin
  install -D -p -m 0644 ${B}/bin/bl1_provisioning_bundle.bin ${D}/firmware/bl1_provisioning_bundle.bin
}

create_bl1_image(){
    dd conv=notrunc bs=1 if=${D}/firmware/bl1_1.bin of=${D}/firmware/bl1.bin seek=0
    # Size of bl1_1.bin is 58KB (59392 bytes)  
    dd conv=notrunc bs=1 if=${D}/firmware/bl1_provisioning_bundle.bin of=${D}/firmware/bl1.bin seek=59392
}
do_install[postfuncs] += "create_bl1_image"
