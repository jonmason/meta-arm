DESCRIPTION = "Trusted Firmware-A Tests"
LICENSE = "BSD & Apache-2.0"

PROVIDES = "virtual/tf-a-tests"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

COMPATIBLE_MACHINE ?= "invalid"

# Platform must be set for each machine
TFA_TESTS_PLATFORM ?= "invalid"

# Build for debug (set TFA_TESTS_DEBUG to 1 to activate)
TFA_TESTS_DEBUG ?= "0"

# Sub-directory in which to build.
# This must be coherent with BUILD_PLAT make parameter so that deploy can find
# the produced binaries
#TFA_TESTS_BUILD_DIR ?= "build-${TFA_TESTS_PLATFORM}"
TFA_TESTS_BUILD_DIR ?= "build/${TFA_TESTS_PLATFORM}/debug"

# set BUILD_PLAT depending on configured BUILD_DIR
EXTRA_OEMAKE += "BUILD_PLAT=${TFA_TESTS_BUILD_DIR}"

# What to build
TFA_TESTS_BUILD_TARGET ?= "tftf"

# What to install
# do_deploy will install everything listed in this
# variable. It is set by default to TFA_TESTS_BUILD_TARGET
TFA_TESTS_INSTALL_TARGET ?= "${TFA_TESTS_BUILD_TARGET}"

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
EXTRA_OEMAKE += "PLAT=${TFA_TESTS_PLATFORM}"

# Handle TFA_TESTS_DEBUG parameter
EXTRA_OEMAKE += "${@bb.utils.contains('TFA_TESTS_DEBUG', '1', ' DEBUG=${TFA_TESTS_DEBUG}', '', d)}"

do_clean() {
    if [ -f ${S}/Makefile ]; then
        oe_runmake -C ${S} distclean
    fi
}

do_compile() {
    oe_runmake ${TFA_TESTS_BUILD_TARGET}
}

do_deploy() {
    install -d -m 755 ${DEPLOYDIR}
    for bldfile in ${TFA_TESTS_INSTALL_TARGET}; do
        if [ "$bldfile" = "all" ]; then
            # Target all is not handled by default
            bberror "all as TFA_TESTS_INSTALL_TARGET is not handled"
            bberror "Please specify valid targets in TFA_TESTS_INSTALL_TARGET"
            bberror "or rewrite or turn off do_deploy"
            exit 1
        elif [ -f ${S}/${TFA_TESTS_BUILD_DIR}/$bldfile ]; then
            echo "Install $bldfile"
            install -m 0644 ${S}/${TFA_TESTS_BUILD_DIR}/$bldfile \
                ${DEPLOYDIR}/$bldfile
        else
            bberror "Unsupported TFA_TESTS_INSTALL_TARGET target $bldfile"
            exit 1
        fi
    done
}
addtask deploy before do_build after do_compile
