# Corstone1000 machines specific TFM support

COMPATIBLE_MACHINE = "(corstone1000)"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/corstone1000:"

SRC_URI:append = " \
      file://0001-corstone1000-disable-secure-debug-temporarily.patch \
      file://0002-corstone1000-provision-firmware-update-metadata-fwu.patch \
      file://0003-corstone1000-parse-the-uefi-firmware-update-capsule.patch \
      file://0004-corstone1000-add-firmware-update-fwu-agent-into-TF-M.patch \
      file://0005-corstone1000-implement-corstone1000_fwu_flash_images.patch \
      file://0006-corstone1000-add-logic-to-select-boot-bank.patch \
      file://0007-corstone1000-integrate-watchdog-driver.patch \
      file://0008-corstone1000-impelment-accept-image-logic.patch \
      file://0009-corstone1000-implement-select-previous-bank-logic.patch \
      file://0010-corstone1000-implement-corstone1000_fwu_host_ack.patch \
      file://0011-SPM-multiple-core-initailize-multi-core-communicatio.patch \
      file://0012-corstone1000-implement-timer-to-track-host-progress.patch \
      file://0013-corstone1000-fwu-nv-counter-anti-rollback-support.patch \
      file://0014-corstone1000-bug-fix-in-openamp-version.patch \
      file://0015-corstone1000-secure-host-watchdog-interrupt-handler.patch \
"

TFM_DEBUG = "1"

## Default is the MPS3 board
TFM_PLATFORM_IS_FVP ?= "FALSE"
EXTRA_OECMAKE += "-DPLATFORM_IS_FVP=${TFM_PLATFORM_IS_FVP}"

SRCBRANCH_tfm = "master"
SRCREV_tfm = "a0a266a55b56929cae5f1777e28926b8421492a6"
SRCREV_mcuboot = "29099e1d17f93ae1d09fe945ad191b703aacd3d8"

# The install task signs the TF-A BL2 and FIP binaries.
# So they need to be copied to the sysroot. Hence the dependencies below:
do_prepare_recipe_sysroot[depends]+= "virtual/trusted-firmware-a:do_populate_sysroot"

# adding host images signing support
require trusted-firmware-m-sign-host-images.inc

do_install() {
  install -D -p -m 0644 ${B}/install/outputs/ARM/CORSTONE1000/tfm_s_signed.bin ${D}/firmware/tfm_s_signed.bin
  install -D -p -m 0644 ${B}/install/outputs/ARM/CORSTONE1000/bl2_signed.bin ${D}/firmware/bl2_signed.bin
  install -D -p -m 0644 ${B}/install/outputs/ARM/CORSTONE1000/bl1.bin ${D}/firmware/bl1.bin

  #
  # Signing TF-A BL2 and the FIP image
  #

  sign_host_image ${TFA_BL2_BINARY} ${RECIPE_SYSROOT}/firmware ${TFA_BL2_RE_IMAGE_LOAD_ADDRESS} ${TFA_BL2_RE_SIGN_BIN_SIZE}

  fiptool update \
      --tb-fw ${D}/firmware/signed_${TFA_BL2_BINARY} \
      ${RECIPE_SYSROOT}/firmware/${TFA_FIP_BINARY}

  sign_host_image ${TFA_FIP_BINARY} ${RECIPE_SYSROOT}/firmware ${TFA_FIP_RE_IMAGE_LOAD_ADDRESS} ${TFA_FIP_RE_SIGN_BIN_SIZE}
}
