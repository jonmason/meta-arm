require optee-os.inc

SRCREV = "023e33656e2c9557ce50ad63a98b2e2c9b51c118"

SRC_URI_append = " \
    file://0001-mk-compile.mk-fix-cc-option-macro.patch \
    file://0002-Allow-use-of-cc-option-in-core-arch-arm-arm.mk.patch \
    file://0003-arm64-Disable-outline-atomics-when-compiling.patch \
    file://0004-Cleanup-unused-comp-cflags-sm-from-libgcc-lookup-com.patch \
    file://0005-Fixup-Allow-use-of-cc-option-in-core-arch-arm-arm.mk.patch \
    file://allow-setting-sysroot-for-libgcc-lookup-for-3.8.0.patch\
    file://missing-mkdir.patch \
"
