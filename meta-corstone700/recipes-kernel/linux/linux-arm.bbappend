SUMMARY = "Linux Kernel provided and supported by Arm/Linaro for Cortex-A32"

KERNEL_IMAGETYPE = "xipImage"

KBUILD_DEFCONFIG = "corstone700_defconfig"

SRC_URI = "git://${USER}@git.linaro.org/landing-teams/working/arm/kernel-release.git;protocol=https;branch=iota"
SRCREV="76d4729645345cc54d30e28511b94efb16ee117b"
