require optee-os.inc

SRCREV = "c4def2a8262a03244d9a88461699b9b8e43c6b55"

SRC_URI_append = " \
    file://0006-allow-setting-sysroot-for-libgcc-lookup.patch \
    file://0007-allow-setting-sysroot-for-clang.patch \
    file://0001-libutils-provide-empty-__getauxval-implementation.patch \
    file://0002-link.mk-implement-support-for-libnames-after-libgcc-.patch \
    file://0003-ta_dev_kit.mk-make-sure-that-libutils-is-linked-seco.patch \
"
