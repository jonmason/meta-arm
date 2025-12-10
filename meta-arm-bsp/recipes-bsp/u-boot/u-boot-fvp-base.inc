# FVP base specific U-boot support

SRC_URI:append = " \
    file://virtio-boot.cfg \
    file://0001-vexpress64-Set-the-DM_RNG-property.patch \
    file://0002-arm-vexpress64-Enable-SYSRESET-and-SYSRESET_PSCI.patch \
    file://0003-vexpress64-Imply-CONFIG_ARM64_CRC32-by-default.patch \
    "

# Remove backported patches from latest version
SRC_URI:remove:class-devupstream = " \
    file://0001-vexpress64-Set-the-DM_RNG-property.patch \
    file://0002-arm-vexpress64-Enable-SYSRESET-and-SYSRESET_PSCI.patch \
    "
