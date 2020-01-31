SUMMARY = "External system Cortex-M3 Firmware"
DESCRIPTION = "External system Firmware"
HOMEPAGE = "https://gerrit.oss.arm.com/#/admin/projects/EP/src/ExternalSystem"
DEPENDS += " coreutils-native gcc-arm-none-eabi-native"
LICENSE="BSD"
LIC_FILES_CHKSUM = "file://license.md;md5=e44b2531cd6ffe9dece394dbe988d9a0"

# Use Yocto-built python3 executable
inherit python3native

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI = "gitsm://${USER}@git.linaro.org/landing-teams/working/arm/external-system.git;protocol=https;branch=master"
SRCREV="211f64282cde60e87eb030500cb8ebbd03eba328"
S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

COMPATIBLE_MACHINE = "(corstone700)"

PLATFORM = "corstone-700"

LDFLAGS[unexport] = "1"

DEBUG_PREFIX_MAP_pn-external-system = "-fdebug-prefix-map=${WORKDIR}=/usr/src/debug/${PN}/${EXTENDPE}${PV}-${PR} \
                        -fdebug-prefix-map=${STAGING_DIR_HOST}= \
                        -fdebug-prefix-map=${STAGING_DIR_NATIVE}= \
                        "


do_compile() {
    export PATH=${TC_GCC_ARM_NONE_EABI_BIN}:$PATH
    mkdir -p ${B}
    oe_runmake -C ${S} BUILD_BASE=${B} \
        BUILD_PLAT=${B}/${PLATFORM}/ \
        PRODUCT=${PLATFORM} \
        CROSS_COMPILE=arm-none-eabi- \
        clean \
        all
    cp ${S}/build/product/${PLATFORM}/firmware/release/bin/firmware.bin ${B}/es_flashfw.bin
}

do_install() {
    install -D -p -m 0644 ${B}/es_flashfw.bin ${DEPLOY_DIR_IMAGE}/es_flashfw.bin
}
