require optee-os.inc

SRCREV = "f9e550142dd4b33ee1112f5dd64ffa94ba79cefa"

SRC_URI:append = " \
    file://0006-allow-setting-sysroot-for-libgcc-lookup.patch \
    file://0007-allow-setting-sysroot-for-clang.patch \
   "
DEPENDS += "dtc-native"
