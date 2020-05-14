DESCRIPTION = "TF-A spm"
LICENSE = "BSD & Apache-2.0"

PROVIDES = "virtual/spm"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

COMPATIBLE_MACHINE ?= "invalid"

inherit pythonnative

# Platform must be set for each machine
SPM_PLATFORM ?= "invalid"

# Build for debug (set SPM_DEBUG to 1 to activate)
SPM_DEBUG ?= "0"

# hafnium project
SPM_PROJECT ?= "reference"

# This is fixed for SPM
SPM_BUILD_DIR ?= "out/${SPM_PROJECT}"

# platform build directory
SPM_BUILD_DIR_PLAT ?= "${SPM_BUILD_DIR}/${SPM_PLATFORM}"

# set project to build
EXTRA_OEMAKE += "PROJECT=${SPM_PROJECT}"

SPM_BUILD_TARGET ?= "hafnium.bin"

# do_deploy will install everything listed in this
# variable. It is set by default to SPM_BUILD_TARGET
SPM_INSTALL_TARGET ?= "${SPM_BUILD_TARGET}"

# Requires CROSS_COMPILE set by hand as there is no configure script

# Currently SPM uses complier from prebuilts submodule. CROSS_COMPILE will
# be set once prebuilts dependencies are removed.
#export CROSS_COMPILE="${TARGET_PREFIX}"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS
# as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

# No configure or install
do_configure[noexec] = "1"
do_install[noexec] = "1"

# needs bison, bc
DEPENDS_append = " bison-native bc-native"


# Handle SPM_DEBUG parameter
EXTRA_OEMAKE += "${@bb.utils.contains('SPM_DEBUG', '1', ' DEBUG=${SPM_DEBUG}', '', d)}"

do_compile() {
    oe_runmake
}

do_deploy() {
    install -d -m 755 ${DEPLOYDIR}
    for bldfile in ${SPM_INSTALL_TARGET}; do
        if [ "$bldfile" = "all" ]; then
            # Target all is not handled by default
            bberror "all as SPM_INSTALL_TARGET is not handled"
            bberror "Please specify valid targets in SPM_INSTALL_TARGET"
            bberror "or rewrite or turn off do_deploy"
            exit 1
        elif [ -f ${S}/${SPM_BUILD_DIR_PLAT}/$bldfile ]; then
            echo "Install $bldfile"
            install -m 0755 ${S}/${SPM_BUILD_DIR_PLAT}/$bldfile \
                ${DEPLOYDIR}/$bldfile
        else
            bberror "Unsupported SPM_INSTALL_TARGET target $bldfile"
            exit 1
        fi
    done
}
addtask deploy before do_build after do_compile
