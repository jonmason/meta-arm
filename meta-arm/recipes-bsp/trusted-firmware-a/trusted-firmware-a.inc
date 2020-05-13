DESCRIPTION = "Trusted Firmware-A"
LICENSE = "BSD & Apache-2.0"

PROVIDES = "virtual/trusted-firmware-a"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy nopackages

COMPATIBLE_MACHINE ?= "invalid"

# Platform must be set for each machine
TFA_PLATFORM ?= "invalid"

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

# What to build
# By default we only build bl1, do_deploy will copy
# everything listed in this variable (by default bl1.bin)
TFA_BUILD_TARGET ?= "bl1"

# What to install
# do_install and do_deploy will install everything listed in this
# variable. It is set by default to TFA_BUILD_TARGET
TFA_INSTALL_TARGET ?= "${TFA_BUILD_TARGET}"

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

# Add platform parameter
EXTRA_OEMAKE += "BUILD_BASE=${B} PLAT=${TFA_PLATFORM}"

# Handle TFA_DEBUG parameter
EXTRA_OEMAKE += "${@bb.utils.contains('TFA_DEBUG', '1', ' DEBUG=${TFA_DEBUG}', '', d)}"

# Handle MBEDTLS
EXTRA_OEMAKE += "${@bb.utils.contains('TFA_MBEDTLS', '1', ' MBEDTLS_DIR=${TFA_MBEDTLS_DIR}', '', d)}"

# Uboot support
DEPENDS += " ${@bb.utils.contains('TFA_UBOOT', '1', 'u-boot', '', d)}"
do_compile[depends] += " ${@bb.utils.contains('TFA_UBOOT', '1', 'u-boot:do_deploy', '', d)}"
EXTRA_OEMAKE += "${@bb.utils.contains('TFA_UBOOT', '1', ' BL33=${DEPLOY_DIR_IMAGE}/u-boot.bin', '',d)}"

# The following hack is needed to fit properly in yocto build environment
# TFA is forcing the host compiler and its flags in the Makefile using :=
# assignment for GCC and CFLAGS.
do_compile() {
    cd ${S}

    # These changes are needed to have the fiptool compiling and executing properly
    sed -i '/^LDLIBS/ s,$, \-L${RECIPE_SYSROOT_NATIVE}${libdir},' ${S}/tools/fiptool/Makefile
    sed -i '/^INCLUDE_PATHS/ s,$, \-I${RECIPE_SYSROOT_NATIVE}${includedir},' ${S}/tools/fiptool/Makefile
    export LD_LIBRARY_PATH=${STAGING_DIR_NATIVE}${libdir}:$LD_LIBRARY_PATH

    oe_runmake ${TFA_BUILD_TARGET}
}
do_compile[cleandirs] = "${B}"

do_install() {
    if ${@"true" if d.getVar('TFA_DEBUG') == '1' else "false"}; then
        BUILD_PLAT=${B}/${TFA_PLATFORM}/debug/
    else
        BUILD_PLAT=${B}/${TFA_PLATFORM}/release/
    fi

    install -d -m 755 ${D}/firmware
    for atfbin in ${TFA_INSTALL_TARGET}; do
        if [ "$atfbin" = "all" ]; then
            # Target all is not handled by default
            bberror "all as TFA_INSTALL_TARGET is not handled by do_install"
            bberror "Please specify valid targets in TFA_INSTALL_TARGET or"
            bberror "rewrite or turn off do_install"
            exit 1
        elif [ -f $BUILD_PLAT/$atfbin.bin ]; then
            echo "Install $atfbin.bin"
            install -m 0644 $BUILD_PLAT/$atfbin.bin \
                ${D}/firmware/$atfbin-${TFA_PLATFORM}.bin
        elif [ -f $BUILD_PLAT/$atfbin/$atfbin.elf ]; then
            echo "Install $atfbin.elf"
            install -m 0644 $BUILD_PLAT/$atfbin/$atfbin.elf \
                ${D}/firmware/$atfbin-${TFA_PLATFORM}.elf
        elif [ -f $BUILD_PLAT/$atfbin ]; then
            echo "Install $atfbin"
            install -m 0644 $BUILD_PLAT/$atfbin \
                ${D}/firmware/$atfbin-${TFA_PLATFORM}
        elif [ "$atfbin" = "dtbs" ]; then
            echo "dtbs install, skipped"
        elif [ -f ${B}/tools/$atfbin/$atfbin ]; then
            echo "Tools $atfbin install, skipped"
        else
            bberror "Unsupported TFA_INSTALL_TARGET target $atfbin"
            exit 1
        fi
    done
}

SYSROOT_DIRS += "/firmware"

do_deploy() {
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
addtask deploy after do_install
