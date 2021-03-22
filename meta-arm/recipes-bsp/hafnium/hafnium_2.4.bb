SUMMARY = "Hafnium"
DESCRIPTION = "A reference Secure Partition Manager (SPM) for systems that implement the Armv8.4-A Secure-EL2 extension"
LICENSE = "BSD-3-Clause & GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=782b40c14bad5294672c500501edc103"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy python3native

SRC_URI = "gitsm://git.trustedfirmware.org/hafnium/hafnium.git;protocol=https"
SRCREV = "410a3acaf669c12d41fb4c57fcaf3ecee6fdba61"
S = "${WORKDIR}/git"

COMPATIBLE_MACHINE ?= "invalid"

# Default build 'reference'
HAFNIUM_PROJECT ?= "reference"

# Platform must be set for each machine
HAFNIUM_PLATFORM ?= "invalid"

# hafnium build directory
# Append _clang as the build rule in hafnium adds this to the platform name.
HAFNIUM_BUILD_DIR_PLAT = "out/${HAFNIUM_PROJECT}/${HAFNIUM_PLATFORM}_clang"

# do_deploy will install everything listed in this variable. It is set by
# default to hafnium
HAFNIUM_INSTALL_TARGET ?= "hafnium"

DEPENDS = "bison-native bc-native"

# set project to build
EXTRA_OEMAKE += "PROJECT=${HAFNIUM_PROJECT}"

do_compile_prepend() {
    # Hafnium expects 'python'. Create symlink python to python3
    real=$(which ${PYTHON})
    ln -snf $real $(dirname $real)/python
}

do_install() {
    install -d -m 755 ${D}/firmware
    for bldfile in ${HAFNIUM_INSTALL_TARGET}; do
        processed="0"
        if [ -f ${S}/${HAFNIUM_BUILD_DIR_PLAT}/$bldfile.bin ]; then
            echo "Install $bldfile.bin"
            install -m 0755 ${S}/${HAFNIUM_BUILD_DIR_PLAT}/$bldfile.bin \
                ${D}/firmware/$bldfile-${HAFNIUM_PLATFORM}.bin
            ln -sf $bldfile-${HAFNIUM_PLATFORM}.bin ${D}/firmware/$bldfile.bin
            processed="1"
        fi
        if [ -f ${S}/${HAFNIUM_BUILD_DIR_PLAT}/$bldfile.elf ]; then
            echo "Install $bldfile.elf"
            install -m 0755 ${S}/${HAFNIUM_BUILD_DIR_PLAT}/$bldfile.elf \
                ${D}/firmware/$bldfile-${HAFNIUM_PLATFORM}.elf
            ln -sf $bldfile-${HAFNIUM_PLATFORM}.elf ${D}/firmware/$bldfile.elf
            processed="1"
        fi
        if [ "$processed" = "0" ]; then
            bberror "Unsupported HAFNIUM_INSTALL_TARGET target $bldfile"
            exit 1
        fi
    done
}

FILES_${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"
# skip QA tests: {'ldflags'}
INSANE_SKIP_${PN} = "ldflags"

do_deploy() {
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
addtask deploy after do_install

python() {
    # https://developer.trustedfirmware.org/T898
    if d.getVar("BUILD_ARCH") != "x86_64":
        raise bb.parse.SkipRecipe("Cannot be built on non-x86-64 hosts")
}
