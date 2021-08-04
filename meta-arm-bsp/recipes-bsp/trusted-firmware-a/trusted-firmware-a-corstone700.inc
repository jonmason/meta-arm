# Corstone700 machines specific TFA support

COMPATIBLE_MACHINE = "(corstone700-*)"

TFA_DEBUG = "1"
TFA_UBOOT = "1"
TFA_BUILD_TARGET = "all fip"
TFA_INSTALL_TARGET = "fip.bin"

EXTRA_OEMAKE:append = " \
                        ARCH=aarch32 \
                        TARGET_PLATFORM=${TFA_TARGET_PLATFORM} \
                        AARCH32_SP=sp_min \
                        ARM_LINUX_KERNEL_AS_BL33=0 \
                        RESET_TO_SP_MIN=1 \
                        ENABLE_PIE=1 \
                        ARM_PRELOADED_DTB_BASE=0x80400000 \
                        "
