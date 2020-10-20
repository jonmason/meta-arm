SUMMARY = "UEFI EDK2 Firmware"
DESCRIPTION = "UEFI EDK2 Firmware for Arm reference platforms"
HOMEPAGE = "https://github.com/tianocore/edk2"

LICENSE = "BSD-2-Clause-Patent"

PROVIDES += "virtual/uefi-firmware"

# EDK2
LIC_FILES_CHKSUM = "file://edk2/License.txt;md5=2b415520383f7964e96700ae12b4570a"
# EDK2 Platforms
LIC_FILES_CHKSUM += "file://edk2/edk2-platforms/License.txt;md5=2b415520383f7964e96700ae12b4570a"

SRC_URI ?= "\
    git://github.com/tianocore/edk2.git;name=edk2;destsuffix=${S}/edk2;nobranch=1 \
    git://github.com/tianocore/edk2-platforms.git;name=edk2-platforms;destsuffix=${S}/edk2/edk2-platforms;nobranch=1 \
"
SRCREV_edk2           ?= "6ff7c838d09224dd4e4c9b5b93152d8db1b19740"
SRCREV_edk2-platforms ?= "ed4cc8059ec551032f0d8b8c172e9ec19214a638"
SRCREV_FORMAT         = "edk2_edk2-platforms"

EDK2_BUILD_RELEASE   ?= "0"
EDK2_PLATFORM        ?= "invalid"
EDK2_PLATFORM_DSC    ?= ""
EDK2_BIN_NAME        ?= ""
EDK2_ARCH            ?= ""

EDK2_BUILD_MODE = "${@bb.utils.contains('EDK2_BUILD_RELEASE', '1', 'RELEASE', 'DEBUG', d)}"

DEPENDS += "util-linux-native iasl-native"

inherit deploy

B = "${WORKDIR}/build"
S = "${WORKDIR}/git"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE ?= "invalid"

LDFLAGS[unexport] = "1"

# No configure
do_configure[noexec] = "1"

# Set variables as per envsetup
export GCC5_AARCH64_PREFIX = "${STAGING_BINDIR_TOOLCHAIN}/${TARGET_PREFIX}"
export PACKAGES_PATH       = "${S}/edk2:${S}/edk2/edk2-platforms"
export WORKSPACE           = "${S}/edk2"
export EDK_TOOLS_PATH      = "${WORKSPACE}/BaseTools"
export PYTHON_COMMAND      = "python3"
export CONF_PATH           = "${WORKSPACE}/Conf"

export BTOOLS_PATH = "${EDK_TOOLS_PATH}/BinWrappers/PosixLike"

GCC_VER ?= "GCC5"

do_compile() {
    sed -i -e 's:-I \.\.:-I \.\. ${BUILD_CFLAGS} :' ${EDK_TOOLS_PATH}/Source/C/Makefiles/header.makefile
    sed -i -e 's: -luuid: -luuid ${BUILD_LDFLAGS}:g' ${EDK_TOOLS_PATH}/Source/C/*/GNUmakefile

    # Copy the templates as we don't run envsetup
    cp ${EDK_TOOLS_PATH}/Conf/build_rule.template ${WORKSPACE}/Conf/build_rule.txt
    cp ${EDK_TOOLS_PATH}/Conf/tools_def.template ${WORKSPACE}/Conf/tools_def.txt
    cp ${EDK_TOOLS_PATH}/Conf/target.template ${WORKSPACE}/Conf/target.txt

    # Build basetools
    oe_runmake -C ${S}/edk2/BaseTools

    PATH="${WORKSPACE}:${BTOOLS_PATH}:$PATH" \
    "${S}/edk2/BaseTools/BinWrappers/PosixLike/build" \
       -a "${EDK2_ARCH}" \
       -b ${EDK2_BUILD_MODE} \
       -t ${GCC_VER} \
       -p "${S}/edk2/edk2-platforms/Platform/ARM/${EDK2_PLATFORM_DSC}"
}

do_install() {
    install -d ${D}/firmware
    install "${S}/edk2/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${GCC_VER}/FV/${EDK2_BIN_NAME}" "${D}/firmware/uefi.bin"
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
