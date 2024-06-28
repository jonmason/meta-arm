FILESEXTRAPATHS:prepend:corstone1000 := "${THISDIR}/corstone1000/${PN}:"

COMPATIBLE_MACHINE:corstone1000 = "corstone1000"
SRC_URI:append:corstone1000 = " \
  file://0001-newlib-memcpy-remove-optimized-version.patch;patchdir=../newlib \
"
export NEWLIB_CFLAGS_TARGET = "-Wno-implicit-function-declaration -Wno-int-conversion"

COMPATIBLE_MACHINE:fvp-base = "fvp-base"
