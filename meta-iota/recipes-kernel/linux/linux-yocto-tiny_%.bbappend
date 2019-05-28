S = "${WORKDIR}/linux-${PV}"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI = " \
	   git://git.linaro.org/landing-teams/working/arm/kernel-testing.git;protocol=https;branch=tinylinux_giot_demo \
          "

SRCREV = "135e79d294c9ec552687cccd3a28147d2df69d29"
SRCREV_machine = "135e79d294c9ec552687cccd3a28147d2df69d29"

KBUILD_DEFCONFIG_vexpress-a5 ?= "tiny_vexpress_defconfig"

COMPATIBLE_MACHINE += "|vexpress-a5"

do_preconfigure() {
	mkdir -p ${B}
	echo "" > ${B}/.config
	CONF_SED_SCRIPT=""

	kernel_conf_variable LOCALVERSION "\"${LOCALVERSION}\""
	kernel_conf_variable LOCALVERSION_AUTO y

	sed -e "${CONF_SED_SCRIPT}" < '${S}/arch/arm/configs/${KBUILD_DEFCONFIG_vexpress}' >> '${B}/.config'

	if [ "${SCMVERSION}" = "y" ]; then
		# Add GIT revision to the local version
		head=`git --git-dir=${S}/.git rev-parse --verify --short HEAD 2> /dev/null`
		printf "%s%s" +g $head > ${S}/.scmversion
	fi
}

do_install_append() {
        install -d ${D}/boot
}

ALLOW_EMPTY_kernel-devicetree = "1"