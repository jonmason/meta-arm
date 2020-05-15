SUMMARY = "OP-TEE Trusted OS"
DESCRIPTION = "Open Portable Trusted Execution Environment - Trusted side of the TEE"
HOMEPAGE = "https://www.op-tee.org/"

LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=c1f21c4f72f372ef38a5a4aee55ec173"

PV = "3.8.0+git${SRCPV}"

inherit deploy python3native
require optee.inc

DEPENDS = "python3-pycryptodome-native python3-pycryptodomex-native python3-pyelftools-native"

SRCREV = "023e33656e2c9557ce50ad63a98b2e2c9b51c118"
SRC_URI = " \
    git://github.com/OP-TEE/optee_os.git \
    file://0001-allow-setting-sysroot-for-libgcc-lookup.patch \
"

S = "${WORKDIR}/git"

OPTEEMACHINE ?= "${MACHINE}"
OPTEEOUTPUTMACHINE ?= "${MACHINE}"

OPTEE_ARCH = "null"
OPTEE_ARCH_armv7a = "arm32"
OPTEE_ARCH_aarch64 = "arm64"
OPTEE_CORE = "${@d.getVar('OPTEE_ARCH').upper()}"

EXTRA_OEMAKE = " \
    PLATFORM=${OPTEEMACHINE} \
    CFG_${OPTEE_CORE}_core=y \
    CROSS_COMPILE_core=${HOST_PREFIX} \
    CROSS_COMPILE_ta_${OPTEE_ARCH}=${HOST_PREFIX} \
    NOWERROR=1 \
    V=1 \
    ta-targets=ta_${OPTEE_ARCH} \
    LIBGCC_LOCATE_CFLAGS=--sysroot=${STAGING_DIR_HOST} \
"

CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
CPPFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

do_configure[noexec] = "1"

do_compile() {
    oe_runmake all CFG_TEE_TA_LOG_LEVEL=0
}

do_install() {
    #install core in firmware
    install -d ${D}${nonarch_base_libdir}/firmware/
    install -m 644 ${B}/out/arm-plat-${OPTEEOUTPUTMACHINE}/core/*.bin ${D}${nonarch_base_libdir}/firmware/

    #install TA devkit
    install -d ${D}${includedir}/optee/export-user_ta/
    for f in ${B}/out/arm-plat-${OPTEEOUTPUTMACHINE}/export-ta_${OPTEE_ARCH}/* ; do
        cp -aR $f ${D}${includedir}/optee/export-user_ta/
    done
}

PACKAGE_ARCH = "${MACHINE_ARCH}"

do_deploy() {
    install -d ${DEPLOYDIR}/optee
    install -m 644 ${D}${nonarch_base_libdir}/firmware/* ${DEPLOYDIR}/optee/
}

addtask deploy before do_build after do_install

FILES_${PN} = "${nonarch_base_libdir}/firmware/"
FILES_${PN}-dev = "${includedir}/optee/"

INSANE_SKIP_${PN}-dev = "staticdev"

INHIBIT_PACKAGE_STRIP = "1"
