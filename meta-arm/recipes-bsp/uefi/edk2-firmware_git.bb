SUMMARY = "UEFI EDK2 Firmware"
DESCRIPTION = "UEFI EDK2 Firmware for Arm reference platforms"
HOMEPAGE = "https://github.com/tianocore/edk2"

LICENSE = "BSD-2-Clause-Patent"

PROVIDES += "virtual/uefi-firmware"

# EDK2
LIC_FILES_CHKSUM = "file://License.txt;md5=2b415520383f7964e96700ae12b4570a"
# EDK2 Platforms
LIC_FILES_CHKSUM += "file://edk2-platforms/License.txt;md5=2b415520383f7964e96700ae12b4570a"

# These can be overridden as needed
EDK2_SRC_URI = "gitsm://github.com/tianocore/edk2.git"
EDK2_PLATFORMS_SRC_URI = "git://github.com/tianocore/edk2-platforms.git"

SRC_URI = "\
    ${EDK2_SRC_URI};name=edk2;destsuffix=edk2;nobranch=1 \
    ${EDK2_PLATFORMS_SRC_URI};name=edk2-platforms;destsuffix=edk2/edk2-platforms;nobranch=1 \
"

PV = "202008+git${SRCPV}"
SRCREV_edk2           ?= "06dc822d045c2bb42e497487935485302486e151"
SRCREV_edk2-platforms ?= "7aab81a35aef7b295e73d7d6dfd528cc812790ed"
SRCREV_FORMAT         = "edk2_edk2-platforms"

EDK2_BUILD_RELEASE   ?= "1"
EDK2_PLATFORM        ?= "ArmVirtQemu-AARCH64"
EDK2_PLATFORM_DSC    ?= "ArmVirtPkg/ArmVirtQemu.dsc"
EDK2_BIN_NAME        ?= "QEMU_EFI.fd"
EDK2_ARCH            ?= "AARCH64"

EDK2_BUILD_MODE = "${@bb.utils.contains('EDK2_BUILD_RELEASE', '1', 'RELEASE', 'DEBUG', d)}"

DEPENDS += "util-linux-native iasl-native"

inherit deploy

S = "${WORKDIR}/edk2"
B = "${WORKDIR}/build"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE ?= "qemuarm64"

LDFLAGS[unexport] = "1"

do_configure[cleandirs] += "${B}"

# Set variables as per envsetup
export GCC5_AARCH64_PREFIX = "${STAGING_BINDIR_TOOLCHAIN}/${TARGET_PREFIX}"
export PACKAGES_PATH       = "${S}:${S}/edk2-platforms"
export WORKSPACE           = "${B}"
export EDK_TOOLS_PATH      = "${S}/BaseTools"
export PYTHON_COMMAND      = "python3"
export CONF_PATH           = "${S}/Conf"

export BTOOLS_PATH = "${EDK_TOOLS_PATH}/BinWrappers/PosixLike"

EDK_COMPILER ?= "GCC5"
EDK_COMPILER_toolchain-clang = "CLANG38"

do_compile() {
    sed -i -e 's:-I \.\.:-I \.\. ${BUILD_CFLAGS} :' ${EDK_TOOLS_PATH}/Source/C/Makefiles/header.makefile
    sed -i -e 's: -luuid: -luuid ${BUILD_LDFLAGS}:g' ${EDK_TOOLS_PATH}/Source/C/*/GNUmakefile

    # Copy the templates as we don't run envsetup
    cp ${EDK_TOOLS_PATH}/Conf/build_rule.template ${S}/Conf/build_rule.txt
    cp ${EDK_TOOLS_PATH}/Conf/tools_def.template ${S}/Conf/tools_def.txt
    cp ${EDK_TOOLS_PATH}/Conf/target.template ${S}/Conf/target.txt

    # Build basetools
    oe_runmake -C ${S}/BaseTools

    PATH="${WORKSPACE}:${BTOOLS_PATH}:$PATH" \
    "${S}/BaseTools/BinWrappers/PosixLike/build" \
       -a "${EDK2_ARCH}" \
       -b ${EDK2_BUILD_MODE} \
       -t ${EDK_COMPILER} \
       -p ${EDK2_PLATFORM_DSC}
}

do_install() {
    install -d ${D}/firmware
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/${EDK2_BIN_NAME} ${D}/firmware/uefi.bin
}

FILES_${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"
# Skip QA check for relocations in .text of elf binaries
INSANE_SKIP_${PN} = "textrel"

do_deploy() {
    # Copy the images to deploy directory
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
addtask deploy after do_install
