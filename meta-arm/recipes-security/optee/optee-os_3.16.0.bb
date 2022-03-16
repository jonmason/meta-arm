require optee-os.inc

SRCREV = "d0b742d1564834dac903f906168d7357063d5459"

SRC_URI:append = " \
    file://0006-allow-setting-sysroot-for-libgcc-lookup.patch \
    file://0007-allow-setting-sysroot-for-clang.patch \
"
