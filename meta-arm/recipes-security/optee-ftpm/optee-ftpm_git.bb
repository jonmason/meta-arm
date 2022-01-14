SUMMARY = "OPTEE fTPM Microsoft TA"
DESCRIPTION = "TCG reference implementation of the TPM 2.0 Specification."
HOMEPAGE = "https://github.com/microsoft/ms-tpm-20-ref/"

COMPATIBLE_MACHINE ?= "invalid"
COMPATIBLE_MACHINE:qemuarm64 = "qemuarm64"
COMPATIBLE_MACHINE:qemuarm64-secureboot = "qemuarm64"
COMPATIBLE_MACHINE:qemu-generic-arm64 = "qemu-generic-arm64"

#FIXME - doesn't currently work with clang
TOOLCHAIN = "gcc"

inherit deploy python3native

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=27e94c0280987ab296b0b8dd02ab9fe5"

DEPENDS = "python3-pycryptodome-native python3-pycryptodomex-native python3-pyelftools-native optee-os-tadevkit"

FTPM_UUID="bc50d971-d4c9-42c4-82cb-343fb7f37896"

# SRC_URI = "git://github.com/Microsoft/ms-tpm-20-ref;branch=master"
# Since this is not built as a pseudo TA, we can only use it as a kernel module and not built in.
# The TEE supplicant is also needed to provide access to secure storage.
# Secure storage access required by OP-TEE fTPM TA
# is provided via OP-TEE supplicant that's not available during boot.
# Fix this once we replace this with the MS implementation
SRC_URI = "gitsm://github.com/microsoft/MSRSec;protocol=https;branch=master \
           file://0000-fix-ssl-fallthrough.patch \
           file://0001-add-enum-to-ta-flags.patch"

SRCREV = "81abeb9fa968340438b4b0c08aa6685833f0bfa1"

S = "${WORKDIR}/git"

OPTEE_CLIENT_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TEEC_EXPORT = "${STAGING_DIR_HOST}${prefix}"
TA_DEV_KIT_DIR = "${STAGING_INCDIR}/optee/export-user_ta"

EXTRA_OEMAKE += '\
    CFG_FTPM_USE_WOLF=y \
    TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
    TA_CROSS_COMPILE=${TARGET_PREFIX} \
    CFLAGS="${CFLAGS} --sysroot=${STAGING_DIR_HOST} -I${WORKDIR}/optee-os" \
'

EXTRA_OEMAKE:append:aarch64:qemuall = "\
    CFG_ARM64_ta_arm64=y \
"

PARALLEL_MAKE = ""

do_compile() {
    sed -i 's/-mcpu=$(TA_CPU)//' TAs/optee_ta/fTPM/sub.mk
    # there's also a secure variable storage TA called authvars
    cd ${S}/TAs/optee_ta
    oe_runmake ftpm
}

do_install () {
    mkdir -p ${D}/lib/optee_armtz
    install -D -p -m 0644 ${S}/TAs/optee_ta/out/fTPM/${FTPM_UUID}.ta ${D}/lib/optee_armtz/
    install -D -p -m 0644 ${S}/TAs/optee_ta/out/fTPM/${FTPM_UUID}.stripped.elf ${D}/lib/optee_armtz/
}

do_deploy () {
    install -d ${DEPLOYDIR}/optee
    install -D -p -m 0644 ${S}/TAs/optee_ta/out/fTPM/${FTPM_UUID}.stripped.elf ${DEPLOYDIR}/optee/
}

addtask deploy before do_build after do_install

FILES:${PN} += " \
               ${nonarch_base_libdir}/optee_armtz/${FTPM_UUID}.ta \
               ${nonarch_base_libdir}/optee_armtz/${FTPM_UUID}.stripped.elf \
               "

# Imports machine specific configs from staging to build
PACKAGE_ARCH = "${MACHINE_ARCH}"
INSANE_SKIP:${PN} += "ldflags"
