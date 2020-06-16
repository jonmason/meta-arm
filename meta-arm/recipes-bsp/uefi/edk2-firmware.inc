SUMMARY = "UEFI EDK2 Firmware"

PROVIDES += "virtual/uefi-firmware"

EDK2_BUILD_RELEASE   ?= "0"
EDK2_PLATFORM        ?= "invalid"
EDK2_PLATFORM_DSC    ?= ""
EDK2_BIN_NAME        ?= ""
EDK2_ARCH            ?= ""

EDK2_BUILD_MODE = "${@bb.utils.contains('EDK2_BUILD_RELEASE', '1', 'RELEASE', 'DEBUG', d)}"

DEPENDS += "util-linux-native iasl-native"

inherit python3native
inherit deploy

B = "${WORKDIR}/build"
S = "${WORKDIR}/git"

COMPATIBLE_MACHINE ?= "invalid"

LDFLAGS[unexport] = "1"

# No configure
do_configure[noexec] = "1"

# Set variables as per envsetup
export GCC5_AARCH64_PREFIX = "${STAGING_BINDIR_TOOLCHAIN}/${TARGET_PREFIX}"
export PACKAGES_PATH       = "${S}/edk2:${S}/edk2/edk2-platforms"
export WORKSPACE           = "${S}/edk2"
export EDK_TOOLS_PATH      = "${WORKSPACE}/BaseTools"
export PYTHON_COMMAND      = "${PYTHON}"
export CONF_PATH           = "${WORKSPACE}/Conf"

export BTOOLS_PATH = "${EDK_TOOLS_PATH}/BinWrappers/PosixLike"

python __anonymous() {
    # If GCC Version is greater than 4 then pass GCC5
    # set GCC5 by default
    d.setVar('GCC_VER', 'GCC5')

    # Otherwise pass the corresponding version
    G = d.getVar('GCCVERSION',True).split(".")
    gcc_vlist = ['1', '2', '3', '4']
    if G[0] in gcc_vlist:
        d.setVar('GCC_VER', 'GCC'+G[0])
}

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
