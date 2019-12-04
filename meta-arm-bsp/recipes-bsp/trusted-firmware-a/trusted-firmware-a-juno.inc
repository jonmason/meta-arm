# Juno specific TFA support

COMPATIBLE_MACHINE_juno = "juno"
TFA_PLATFORM_juno = "juno"
TFA_DEBUG_juno = "1"
TFA_MBEDTLS_juno = "1"
TFA_UBOOT_juno = "1"
TFA_BUILD_TARGET_juno = "bl1 fip"

# Firmware image from Linaro
SRC_URI_append_juno = " http://releases.linaro.org/members/arm/platforms/19.06/juno-latest-oe-uboot.zip;name=junofip;subdir=juno-oe-uboot"

SRC_URI[junofip.md5sum] = "01b662b81fa409d55ff298238ad24003"
SRC_URI[junofip.sha256sum] = "b8a3909bb3bc4350a8771b863193a3e33b358e2a727624a77c9ecf13516cec82"

# Add our how images.txt

FILESEXTRAPATHS_prepend_juno := "${THISDIR}/files/${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'juno-xen', 'juno', d)}:"

SRC_URI_append_juno = " \
	file://images-r0.txt \
	file://images-r1.txt \
	file://images-r2.txt \
	file://uEnv.txt \
	"

EXTRA_OEMAKE_append_juno = " SCP_BL2=${WORKDIR}/juno-oe-uboot/SOFTWARE/scp_bl2.bin"

# Build dependencies only for Juno and add them
# doing it with do_deploy_juno[depends] does not work
JUNO_EXTRA_DEPS ?= ""
JUNO_EXTRA_DEPS_juno = ""
JUNO_EXTRA_DEPS_juno += "virtual/kernel:do_deploy"
JUNO_EXTRA_DEPS_juno += "${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'xen:do_deploy', '', d)}"

do_deploy[depends] += "${JUNO_EXTRA_DEPS}"

#
# do_deploy_juno_append or do_deploy_append_juno are not working
# so this file must not be included for other machines then the juno
#
do_deploy_append() {
	cp -a ${S}/${TFA_BUILD_DIR}/bl1.bin \
		${WORKDIR}/juno-oe-uboot/SOFTWARE/bl1.bin

	cp -a ${S}/${TFA_BUILD_DIR}/fip.bin \
		${WORKDIR}/juno-oe-uboot/SOFTWARE/fip.bin

	for f in ${KERNEL_DEVICETREE}; do
		install -m 755 -c ${DEPLOY_DIR_IMAGE}/$(basename $f) \
			${WORKDIR}/juno-oe-uboot/SOFTWARE/.
	done

	cp -aL --remove-destination \
		${DEPLOY_DIR_IMAGE}/Image \
		${WORKDIR}/juno-oe-uboot/SOFTWARE/Image

	if [ "${@bb.utils.contains('DISTRO_FEATURES', 'xen', 'yes', 'no', d)}" = "yes" ]; then
		cp -a \
			${DEPLOY_DIR_IMAGE}/xen-${COMPATIBLE_MACHINE}.efi \
			${WORKDIR}/juno-oe-uboot/SOFTWARE/xen
	fi

    # u-boot environment file
    cp -a ${WORKDIR}/uEnv.txt \
        ${WORKDIR}/juno-oe-uboot/SOFTWARE/

    # Juno images list file
    cp -a --remove-destination ${WORKDIR}/images-r0.txt \
        ${WORKDIR}/juno-oe-uboot/SITE1/HBI0262B/images.txt
    cp -a --remove-destination ${WORKDIR}/images-r1.txt \
        ${WORKDIR}/juno-oe-uboot/SITE1/HBI0262C/images.txt
    cp -a --remove-destination ${WORKDIR}/images-r2.txt \
        ${WORKDIR}/juno-oe-uboot/SITE1/HBI0262D/images.txt

    # Zip the files
    cd ${WORKDIR}/
    tar -zcvf juno-oe-uboot.tar.gz juno-oe-uboot/

    # Deploy the compressed archive to the deploy folder
    install -D -p -m0644 ${WORKDIR}/juno-oe-uboot.tar.gz ${DEPLOYDIR}/juno-oe-uboot.tar.gz

}

