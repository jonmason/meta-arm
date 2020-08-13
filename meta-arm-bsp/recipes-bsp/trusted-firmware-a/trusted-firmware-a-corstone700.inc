# Corstone700 machines specific TFA support

COMPATIBLE_MACHINE = "(corstone700-*)"

TFA_DEBUG = "1"
TFA_UBOOT = "1"
TFA_BUILD_TARGET = "all fip"
TFA_INSTALL_TARGET = "fip.bin"

LIC_FILES_CHKSUM = "file://license.rst;md5=1dd070c98a281d18d9eefd938729b031"

# TF-A v2.3 is not used because the following commit is needed:
# corstone700: splitting the platform support into FVP and FPGA
SRCREV_tfa = "ef93cfa3a2591084307a41e64f1cbba327310749"

PV = "2.3+git${SRCPV}"

EXTRA_OEMAKE_append = " \
                        ARCH=aarch32 \
                        TARGET_PLATFORM=${TFA_TARGET_PLATFORM} \
                        AARCH32_SP=sp_min \
                        ARM_LINUX_KERNEL_AS_BL33=0 \
                        RESET_TO_SP_MIN=1 \
                        ENABLE_PIE=1 \
                        ARM_PRELOADED_DTB_BASE=0x80400000 \
                        "
