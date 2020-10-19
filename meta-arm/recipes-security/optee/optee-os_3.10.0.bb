require optee-os.inc

SRCREV = "d1c635434c55b7d75eadf471bde04926bd1e50a7"

SRC_URI_append = " \
    file://0006-allow-setting-sysroot-for-libgcc-lookup.patch \
    file://0007-allow-setting-sysroot-for-clang.patch \
"

