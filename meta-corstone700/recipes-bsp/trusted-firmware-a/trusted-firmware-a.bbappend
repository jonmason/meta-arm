DEPENDS_corstone700 += " dtc-native coreutils-native  "

LIC_FILES_CHKSUM_corstone700 = "file://license.rst;md5=c709b197e22b81ede21109dbffd5f363"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_corstone700 = "\
	git://${USER}@git.linaro.org/landing-teams/working/arm/arm-tf.git;protocol=https;branch=corstone700-19.02 \
	"
SRCREV_corstone700 = "${AUTOREV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

COMPATIBLE_MACHINE = "(corstone700)"

PLATFORM_corstone700 = "corstone700"

LDFLAGS[unexport] = "1"

do_compile_corstone700() {
    mkdir -p ${B}

   oe_runmake -C ${S} BUILD_BASE=${B} \
      BUILD_PLAT=${B}/${PLATFORM}/ \
      PLAT=${PLATFORM} \
      DEBUG=1 \
      ARCH=aarch32 \
      CROSS_COMPILE=${TARGET_PREFIX} \
      AARCH32_SP=sp_min \
      RESET_TO_SP_MIN=1 \
      ARM_LINUX_KERNEL_AS_BL33=1 \
      PRELOADED_BL33_BASE=0x08500000 \
      ARM_PRELOADED_DTB_BASE=0x02800000 \
      ENABLE_STACK_PROTECTOR=strong \
      ENABLE_PIE=1 \
      all \
      fip
}

do_install_corstone700() {
	install -D -p -m 0644 ${B}/${PLATFORM}/fip.bin ${DEPLOY_DIR_IMAGE}/${PLATFORM}.fip
}
