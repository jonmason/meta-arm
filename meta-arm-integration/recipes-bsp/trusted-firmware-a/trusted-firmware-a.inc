DESCRIPTION = "Trusted Firmware-A"
LICENSE = "BSD & Apache-2.0"

PROVIDES = "virtual/trusted-firmware-a"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

COMPATIBLE_MACHINE ?= "invalid"

# Platform must be set for each machine
TFA_PLATFORM ?= "invalid"

# Build for debug (set TFA_DEBUG to 1 to activate)
TFA_DEBUG ?= "0"
TFA_BUILD_DIR ?= "${@bb.utils.contains('TFA_DEBUG', '1', 'build/${TFA_PLATFORM}/debug', 'build/${TFA_PLATFORM}/release', d)}"

# mbed TLS support (set TFA_MBEDTLS to 1 to activate)
TFA_MBEDTLS ?= "0"
TFA_MBEDTLS_DIR ?= "mbedtls"

# U-boot support (set TFA_UBOOT to 1 to activate)
# When U-Boot support is activated BL33 is activated with u-boot.bin file
TFA_UBOOT ?= "0"

# What to build
# By default we only build bl1, do_deploy will install
# everything listed in this variable (by default bl1.bin)
TFA_BUILD_TARGET ?= "bl1"

# What to install
# do_deploy will install everything listed in this
# variable. It is set by default to TFA_BUILD_TARGET
TFA_INSTALL_TARGET ?= "${TFA_BUILD_TARGET}"

# Requires CROSS_COMPILE set by hand as there is no configure script
export CROSS_COMPILE="${TARGET_PREFIX}"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

# No configure or install
do_configure[noexec] = "1"
do_install[noexec] = "1"

# We need dtc for dtbs compilation
# We need openssl for fiptool
DEPENDS_append = " dtc-native openssl-native"

# Add platform parameter
EXTRA_OEMAKE_append = " PLAT=${TFA_PLATFORM}"

# Handle TFA_DEBUG parameter
EXTRA_OEMAKE_append = " ${@bb.utils.contains('TFA_DEBUG', '1', ' DEBUG=${TFA_DEBUG}', '', d)}"

# Handle MBEDTLS
EXTRA_OEMAKE_append = " ${@bb.utils.contains('TFA_MBEDTLS', '1', ' MBEDTLS_DIR=${TFA_MBEDTLS_DIR}', '', d)}"

# Uboot support
DEPENDS += " ${@bb.utils.contains('TFA_UBOOT', '1', 'u-boot', '', d)}"
do_compile[depends] += " ${@bb.utils.contains('TFA_UBOOT', '1', 'u-boot:do_deploy', '', d)}"
EXTRA_OEMAKE_append = " ${@bb.utils.contains('TFA_UBOOT', '1', ' BL33=${DEPLOY_DIR_IMAGE}/u-boot.bin', '',d)}"

do_clean() {
    if [ -f ${S}/Makefile ]; then
        oe_runmake -C ${S} distclean
    fi
}

do_compile() {
    oe_runmake ${TFA_BUILD_TARGET}
}

do_deploy() {
    install -d -m 755 ${DEPLOYDIR}
    for atfbin in ${TFA_INSTALL_TARGET}; do
        if [ "$atfbin" = "all" ]; then
            # Target all is not handled by default
            bberror "all as TFA_INSTALL_TARGET is not handled by do_deploy"
            bberror "Please specify valid targets in TFA_INSTALL_TARGET or"
            bberror "rewrite or turn off do_deploy"
            exit 1
        elif [ -f ${S}/${TFA_BUILD_DIR}/$atfbin.bin ]; then
            echo "Install $atfbin.bin"
            install -m 0644 ${S}/${TFA_BUILD_DIR}/$atfbin.bin \
                ${DEPLOYDIR}/$atfbin-${TFA_PLATFORM}.bin
        elif [ -f ${S}/${TFA_BUILD_DIR}/$atfbin.elf ]; then
            echo "Install $atfbin.elf"
            install -m 0644 ${S}/${TFA_BUILD_DIR}/$atfbin.elf \
                ${DEPLOYDIR}/$atfbin-${TFA_PLATFORM}.elf
        elif [ -f ${S}/${TFA_BUILD_DIR}/$atfbin ]; then
            echo "Install $atfbin"
            install -m 0644 ${S}/${TFA_BUILD_DIR}/$atfbin \
                ${DEPLOYDIR}/$atfbin-${TFA_PLATFORM}
        elif [ "$atfbin" = "dtbs" ]; then
            echo "dtbs install, skipped"
        elif [ -f ${S}/tools/$atfbin/$atfbin ]; then
            echo "Tools $atfbin install, skipped"
        else
            bberror "Unsupported TFA_INSTALL_TARGET target $atfbin"
            exit 1
        fi
    done
}
addtask deploy before do_build after do_compile
