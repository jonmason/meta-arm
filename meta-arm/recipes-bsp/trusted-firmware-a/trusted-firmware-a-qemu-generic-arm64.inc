COMPATIBLE_MACHINE = "qemu-generic-arm64"
DEPENDS:append = " optee-os"

TFA_PLATFORM = "qemu_sbsa"
TFA_BUILD_TARGET = "all fip"
TFA_INSTALL_TARGET = "bl1 fip"

EXTRA_OEMAKE:append = " \
    BL32=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-header_v2.bin \
    BL32_EXTRA1=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-pager_v2.bin \
    BL32_EXTRA2=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-pageable_v2.bin \
    BL32_RAM_LOCATION=tdram \
    "
