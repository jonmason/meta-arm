# FVP specific TFA parameters

#
# Armv8-A Base Platform FVP and Armv8-A Foundation Platform uses the same
# TFAs.
#

COMPATIBLE_MACHINE = "fvp-base|foundation-armv8"
TFA_PLATFORM = "fvp"
TFA_DEBUG = "1"
TFA_MBEDTLS = "1"
TFA_UBOOT = "1"
TFA_BUILD_TARGET = "bl1 bl2 bl31 dtbs fiptool"

do_install[depends] += "virtual/kernel:do_deploy"

do_install_append() {
    ./tools/fiptool/fiptool create \
        --tb-fw ${S}/${TFA_BUILD_DIR}/bl2.bin \
        --soc-fw ${S}/${TFA_BUILD_DIR}/bl31.bin \
        --tb-fw-config ${S}/${TFA_BUILD_DIR}/fdts/fvp_tb_fw_config.dtb \
        --soc-fw-config ${S}/${TFA_BUILD_DIR}/fdts/fvp_soc_fw_config.dtb \
        --hw-config ${DEPLOY_DIR_IMAGE}/$(basename ${KERNEL_DEVICETREE}) \
        --nt-fw ${DEPLOY_DIR_IMAGE}/u-boot.bin \
        fip.bin

    ./tools/fiptool/fiptool info fip.bin

    install -m 0644 ${S}/fip.bin ${D}/firmware/fip-fvp.bin
}
