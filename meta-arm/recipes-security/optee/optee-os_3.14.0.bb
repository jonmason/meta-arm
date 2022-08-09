require optee-os.inc

SRCREV = "d21befa5e53eae9db469eba1685f5aa5c6f92c2f"

SRC_URI:append = " \
    file://0006-allow-setting-sysroot-for-libgcc-lookup.patch \
    file://0007-allow-setting-sysroot-for-clang.patch \
"
DEPENDS = "python3-pycryptodome-native python3-pyelftools-native"

EXTRA_OEMAKE += "LIBGCC_LOCATE_CFLAGS=--sysroot=${STAGING_DIR_HOST}"
