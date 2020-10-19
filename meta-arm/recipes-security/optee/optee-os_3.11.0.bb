require optee-os.inc

SRCREV = "c4def2a8262a03244d9a88461699b9b8e43c6b55"

SRC_URI_append = " \
    file://0006-allow-setting-sysroot-for-libgcc-lookup.patch \
    file://0007-allow-setting-sysroot-for-clang.patch \
"

