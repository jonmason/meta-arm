DESCRIPTION = "Trusted Firmware-A"
LICENSE = "BSD & Apache-2.0"

PROVIDES = "virtual/trusted-firmware-a"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

COMPATIBLE_MACHINE ?= "invalid"
COMPATIBLE_MACHINE_qemuarm64 ?= "qemuarm64"

# Platform must be set for each machine
TFA_PLATFORM ?= "invalid"
TFA_PLATFORM_aarch64_qemuall ?= "qemu"

# Some platforms can have multiple board configurations
# Leave empty for default behavior
TFA_BOARD ?= ""

# Some platforms use SPD (Secure Payload Dispatcher) services
# Few options are "opteed", "tlkd", "trusty", "tspd"...
# Leave empty to not use SPD
TFA_SPD ?= ""
TFA_SPD_aarch64_qemuall ?= "opteed"

# Build for debug (set TFA_DEBUG to 1 to activate)
TFA_DEBUG ?= "0"

B = "${WORKDIR}/build"

# mbed TLS support (set TFA_MBEDTLS to 1 to activate)
TFA_MBEDTLS ?= "0"
# sub-directory in which mbedtls will be downloaded
TFA_MBEDTLS_DIR ?= "mbedtls"
# This should be set to MBEDTLS download URL if MBEDTLS is needed
SRC_URI_MBEDTLS ??= ""
# This should be set to MBEDTLS LIC FILES checksum
LIC_FILES_CHKSUM_MBEDTLS ??= ""
# add MBEDTLS to our sources if activated
SRC_URI += "${@bb.utils.contains('TFA_MBEDTLS', '1', '${SRC_URI_MBEDTLS}', '', d)}"
# add mbed TLS chksum
LIC_FILES_CHKSUM += "${@bb.utils.contains('TFA_MBEDTLS', '1', '${LIC_FILES_CHKSUM_MBEDTLS}', '', d)}"
# add mbed TLS to version
SRCREV_FORMAT_append = "${@bb.utils.contains('TFA_MBEDTLS', '1', '_mbedtls', '', d)}"

# U-boot support (set TFA_UBOOT to 1 to activate)
# When U-Boot support is activated BL33 is activated with u-boot.bin file
TFA_UBOOT ?= "0"
TFA_UBOOT_aarch64_qemuall ?= "1"

# What to build
# By default we only build bl1, do_deploy will copy
# everything listed in this variable (by default bl1.bin)
TFA_BUILD_TARGET ?= "bl1"
TFA_BUILD_TARGET_aarch64_qemuall ?= "all fip"

# What to install
# do_install and do_deploy will install everything listed in this
# variable. It is set by default to TFA_BUILD_TARGET
TFA_INSTALL_TARGET ?= "${TFA_BUILD_TARGET}"
TFA_INSTALL_TARGET_aarch64_qemuall ?= "flash.bin"

# Requires CROSS_COMPILE set by hand as there is no configure script
export CROSS_COMPILE="${TARGET_PREFIX}"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

# No configure
do_configure[noexec] = "1"

# We need dtc for dtbs compilation
# We need openssl for fiptool
DEPENDS_append = " dtc-native openssl-native"
DEPENDS_append_aarch64_qemuall ?= " optee-os"

EXTRA_OEMAKE += "V=1"

# Add platform parameter
EXTRA_OEMAKE += "BUILD_BASE=${B} PLAT=${TFA_PLATFORM}"

# Handle TFA_BOARD parameter
EXTRA_OEMAKE += "${@'TARGET_BOARD=${TFA_BOARD}' if d.getVar('TFA_BOARD') else ''}"

# Handle TFA_SPD parameter
EXTRA_OEMAKE += "${@'SPD=${TFA_SPD}' if d.getVar('TFA_SPD') else ''}"

# Handle TFA_DEBUG parameter
EXTRA_OEMAKE += "${@bb.utils.contains('TFA_DEBUG', '1', 'DEBUG=${TFA_DEBUG}', '', d)}"

# Handle MBEDTLS
EXTRA_OEMAKE += "${@bb.utils.contains('TFA_MBEDTLS', '1', 'MBEDTLS_DIR=${TFA_MBEDTLS_DIR}', '', d)}"

# Uboot support
DEPENDS += " ${@bb.utils.contains('TFA_UBOOT', '1', 'u-boot', '', d)}"
do_compile[depends] += " ${@bb.utils.contains('TFA_UBOOT', '1', 'u-boot:do_deploy', '', d)}"
EXTRA_OEMAKE += "${@bb.utils.contains('TFA_UBOOT', '1', 'BL33=${DEPLOY_DIR_IMAGE}/u-boot.bin', '',d)}"

EXTRA_OEMAKE_append_aarch64_qemuall = " \
    BL32=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-header_v2.bin \
    BL32_EXTRA1=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-pager_v2.bin \
    BL32_EXTRA2=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-pageable_v2.bin \
    BL32_RAM_LOCATION=tdram \
    "

BUILD_DIR = "${B}/${TFA_PLATFORM}"
BUILD_DIR .= "${@'/${TFA_BOARD}' if d.getVar('TFA_BOARD') else ''}"
BUILD_DIR .= "/${@'debug' if d.getVar("TFA_DEBUG") == '1' else 'release'}"

# The following hack is needed to fit properly in yocto build environment
# TFA is forcing the host compiler and its flags in the Makefile using :=
# assignment for GCC and CFLAGS.
do_compile() {
    cd ${S}

    # These changes are needed to have the fiptool compiling and executing properly
    sed -i '/^LDLIBS/ s,$, \$\{BUILD_LDFLAGS},' ${S}/tools/fiptool/Makefile
    sed -i '/^INCLUDE_PATHS/ s,$, \$\{BUILD_CFLAGS},' ${S}/tools/fiptool/Makefile

    oe_runmake ${TFA_BUILD_TARGET}
}
do_compile[cleandirs] = "${B}"

do_compile_append_aarch64_qemuall() {
    # Create a secure flash image for booting AArch64 Qemu. See:
    # https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git/tree/docs/plat/qemu.rst
    dd if=${BUILD_DIR}/bl1.bin of=${BUILD_DIR}/flash.bin bs=4096 conv=notrunc
    dd if=${BUILD_DIR}/fip.bin of=${BUILD_DIR}/flash.bin seek=64 bs=4096 conv=notrunc
}

do_install() {
    install -d -m 755 ${D}/firmware
    for atfbin in ${TFA_INSTALL_TARGET}; do
        processes="0"
        if [ "$atfbin" = "all" ]; then
            # Target all is not handled by default
            bberror "all as TFA_INSTALL_TARGET is not handled by do_install"
            bberror "Please specify valid targets in TFA_INSTALL_TARGET or"
            bberror "rewrite or turn off do_install"
            exit 1
        fi

        if [ -f ${BUILD_DIR}/$atfbin.bin ]; then
            echo "Install $atfbin.bin"
            install -m 0644 ${BUILD_DIR}/$atfbin.bin \
                ${D}/firmware/$atfbin-${TFA_PLATFORM}.bin
            ln -sf $atfbin-${TFA_PLATFORM}.bin ${D}/firmware/$atfbin.bin
            processes="1"
        fi
        if [ -f ${BUILD_DIR}/$atfbin/$atfbin.elf ]; then
            echo "Install $atfbin.elf"
            install -m 0644 ${BUILD_DIR}/$atfbin/$atfbin.elf \
                ${D}/firmware/$atfbin-${TFA_PLATFORM}.elf
            ln -sf $atfbin-${TFA_PLATFORM}.elf ${D}/firmware/$atfbin.elf
            processes="1"
        fi
        if [ -f ${BUILD_DIR}/$atfbin ]; then
            echo "Install $atfbin"
            install -m 0644 ${BUILD_DIR}/$atfbin \
                ${D}/firmware/$atfbin-${TFA_PLATFORM}
            ln -sf $atfbin-${TFA_PLATFORM} ${D}/firmware/$atfbin
            processes="1"
        fi

        if [ "$atfbin" = "dtbs" ]; then
            echo "dtbs install, skipped"
        elif [ -f ${B}/tools/$atfbin/$atfbin ]; then
            echo "Tools $atfbin install, skipped"
        elif [ "$processed" = "0" ]; then
            bberror "Unsupported TFA_INSTALL_TARGET target $atfbin"
            exit 1
        fi
    done
}

FILES_${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"
# Skip QA check for relocations in .text of elf binaries
INSANE_SKIP_${PN} = "textrel"

do_deploy() {
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
addtask deploy after do_install
