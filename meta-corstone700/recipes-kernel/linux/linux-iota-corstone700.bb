SUMMARY = "Linux Kernel provided and supported by ARM/Linaro for Cortex-A32"

require recipes-kernel/linux/linux-iota.inc

# Override do_kernel_configme to avoid kernel being assembled into a linux-yocto style kernel
# https://www.yoctoproject.org/docs/1.8/ref-manual/ref-manual.html#ref-tasks-kernel_configme
do_kernel_configme() {
}

KERNEL_IMAGETYPE = "xipImage"
KBUILD_DEFCONFIG = "corstone700_defconfig"
KBRANCH = ""

SRC_URI = "\
	git://${USER}@git.linaro.org/landing-teams/working/arm/kernel-release.git;protocol=https;branch=corstone700-19.02 \
	"

SRCREV = "${AUTOREV}"
