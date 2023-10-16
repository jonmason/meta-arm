# N1SDP specific TFA support

COMPATIBLE_MACHINE = "rd-v2"
TFA_PLATFORM       = "rdn2"
TFA_BUILD_TARGET   = "all fip"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_DEBUG          = "1"
TFA_UBOOT          = "0"
TFA_UEFI           = "1"

# Enabling Secure-EL1 Payload Dispatcher (SPD)
#TFA_SPD = "spmd"
#TFA_SPMD_SPM_AT_SEL2 = "0"

TF_A_ENABLE_SPM="1"
TF_A_BL31_IN_DRAM="1"
PLAT_DRAM2_SIZE="0x180000000"

#CFLAGS=-DPLAT_DRAM2_SIZE=${PLAT_DRAM2_SIZE}

EXTRA_OEMAKE:append = "\
                     SPM_MM="${TF_A_ENABLE_SPM}" \
                     EL3_EXCEPTION_HANDLING="${TF_A_ENABLE_SPM}" \
                     ARM_BL31_IN_DRAM="${TF_A_BL31_IN_DRAM}" \
		     CSS_SGI_PLATFORM_VARIANT=0 \
		     BL32=${RECIPE_SYSROOT}/firmware/mm_standalone.bin \
		     BL33=${RECIPE_SYSROOT}/firmware/uefi.bin \
		    "
DEPENDS += "edk2-firmware-standalone-mm"
