# Corstone1000 machines specific TFM support

COMPATIBLE_MACHINE = "(corstone1000)"

TFM_DEBUG = "1"

## Default is the MPS3 board
TFM_PLATFORM_IS_FVP ?= "FALSE"
EXTRA_OECMAKE += "-DPLATFORM_IS_FVP=${TFM_PLATFORM_IS_FVP}"
EXTRA_OECMAKE += "-DCC312_LEGACY_DRIVER_API_ENABLED=OFF"

SRCBRANCH_tfm = "master"
SRCREV_tfm = "f8c7e5361b92b16108165601ea81c5d01feb3c22"
SRCREV_mbedtls = "d65aeb37349ad1a50e0f6c9b694d4b5290d60e49"
SRCREV_mcuboot = "29099e1d17f93ae1d09fe945ad191b703aacd3d8"

PV = "1.5.0+git${SRCPV}"
SRCREV_FORMAT = "tfm"

# libmetal
LICENSE += "& BSD-3-Clause"
LIC_FILES_CHKSUM += "file://../libmetal/LICENSE.md;md5=fe0b8a4beea8f0813b606d15a3df3d3c"
SRC_URI += "git://github.com/OpenAMP/libmetal.git;protocol=https;branch=main;name=libmetal;destsuffix=git/libmetal"
SRCREV_libmetal = "f252f0e007fbfb8b3a52b1d5901250ddac96baad"
EXTRA_OECMAKE += "-DLIBMETAL_SRC_PATH=${WORKDIR}/git/libmetal -DLIBMETAL_BIN_PATH=${B}/libmetal-build"

# OpenAMP
LICENSE += "& BSD-2-Clause & BSD-3-Clause"
LIC_FILES_CHKSUM += "file://../openamp/LICENSE.md;md5=a8d8cf662ef6bf9936a1e1413585ecbf"
SRC_URI += "git://github.com/OpenAMP/open-amp.git;protocol=https;branch=main;name=openamp;destsuffix=git/openamp"
SRCREV_openamp = "347397decaa43372fc4d00f965640ebde042966d"
EXTRA_OECMAKE += "-DLIBOPENAMP_SRC_PATH=${WORKDIR}/git/openamp -DLIBOPENAMP_BIN_PATH=${B}/libopenamp-build"

# The install task signs the TF-A BL2 and FIP binaries.
# So they need to be copied to the sysroot. Hence the dependencies below:
do_prepare_recipe_sysroot[depends]+= "trusted-firmware-a:do_populate_sysroot"

# adding host images signing support
require trusted-firmware-m-sign-host-images.inc

do_install() {
  install -D -p -m 0644 ${B}/install/outputs/tfm_s_signed.bin ${D}/firmware/tfm_s_signed.bin
  install -D -p -m 0644 ${B}/install/outputs/bl2_signed.bin ${D}/firmware/bl2_signed.bin
  install -D -p -m 0644 ${B}/install/outputs/bl1.bin ${D}/firmware/bl1.bin

  #
  # Signing TF-A BL2 and the FIP image
  #

  sign_host_image ${TFA_BL2_BINARY} ${RECIPE_SYSROOT}/firmware ${TFA_BL2_RE_IMAGE_LOAD_ADDRESS} ${TFA_BL2_RE_SIGN_BIN_SIZE}

  fiptool update \
      --tb-fw ${D}/firmware/signed_${TFA_BL2_BINARY} \
      ${RECIPE_SYSROOT}/firmware/${TFA_FIP_BINARY}

  sign_host_image ${TFA_FIP_BINARY} ${RECIPE_SYSROOT}/firmware ${TFA_FIP_RE_IMAGE_LOAD_ADDRESS} ${TFA_FIP_RE_SIGN_BIN_SIZE}
}
