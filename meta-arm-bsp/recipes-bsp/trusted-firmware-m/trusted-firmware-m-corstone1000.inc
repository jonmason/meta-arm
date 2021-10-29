# Corstone1000 machines specific TFM support

COMPATIBLE_MACHINE = "(corstone1000)"

TFM_DEBUG = "1"

PACKAGECONFIG[test-secure] = "-DTEST_S=OFF,-DTEST_S=OFF"
PACKAGECONFIG[test-nonsecure] = "-DTEST_NS=OFF,-DTEST_NS=OFF"

INSANE_SKIP:${PN} = "arch"

## Default is the FVP ##
TFM_PLATFORM_IS_FVP ?= "TRUE"
EXTRA_OECMAKE += "-DPLATFORM_IS_FVP=${TFM_PLATFORM_IS_FVP}"

SRCREV_tfm = "ccd82e35f539c0d7261b2935d6d30c550cfc6736"

SRCREV_FORMAT = "tfm_mcuboot_tfm-tests_mbedtls"

do_install() {
  if [ ! -d "${B}/install/outputs/ARM/CORSTONE1000" ]
  then
    bbfatal "'${B}/install/outputs/ARM/CORSTONE1000' output folder not found!"
  fi

  install -D -p -m 0644 ${B}/install/outputs/ARM/CORSTONE1000/tfm_s_signed.bin ${D}/firmware/tfm_s_signed.bin
  install -D -p -m 0644 ${B}/install/outputs/ARM/CORSTONE1000/bl2_signed.bin ${D}/firmware/bl2_signed.bin
  install -D -p -m 0644 ${B}/install/outputs/ARM/CORSTONE1000/bl1.bin ${D}/firmware/bl1.bin

}
