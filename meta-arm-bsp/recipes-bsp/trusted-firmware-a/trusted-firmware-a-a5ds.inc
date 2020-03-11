# Cortex-A5 Designstart specific TFA support

COMPATIBLE_MACHINE = "a5ds"
TFA_PLATFORM = "a5ds"
TFA_DEBUG = "1"
TFA_UBOOT = "1"
TFA_BUILD_TARGET = "all fip"
TFA_INSTALL_TARGET = "bl1.bin fip.bin"

SRCREV = "5d3ee0764b03567bf3501edf47d67d72daff0cb3"
LIC_FILES_CHKSUM = "file://license.rst;md5=1dd070c98a281d18d9eefd938729b031"

EXTRA_OEMAKE_append = " \
                    ARCH=aarch32 \
                    FVP_HW_CONFIG_DTS=fdts/a5ds.dts \
                    ARM_ARCH_MAJOR=7 \
                    AARCH32_SP=sp_min \
                    ARM_CORTEX_A5=yes \
                    ARM_XLAT_TABLES_LIB_V1=1 \
                    "


