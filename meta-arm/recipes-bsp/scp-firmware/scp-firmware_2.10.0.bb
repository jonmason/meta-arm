SUMMARY = "SCP and MCP Firmware"
DESCRIPTION = "Firmware for SCP and MCP software reference implementation"
HOMEPAGE = "https://github.com/ARM-software/SCP-firmware"

LICENSE = "BSD-3-Clause & Apache-2.0"
LIC_FILES_CHKSUM = "file://license.md;beginline=5;md5=9db9e3d2fb8d9300a6c3d15101b19731 \
                    file://contrib/cmsis/git/LICENSE.txt;md5=e3fc50a88d0a364313df4b21ef20c29e"

SRC_URI = "gitsm://github.com/ARM-software/SCP-firmware.git;protocol=https;branch=master"

SRCREV  = "673d014f3861ad81cc5ab06d2884a314a610799b"

PROVIDES += "virtual/control-processor-firmware"

SCP_BUILD_RELEASE   ?= "1"
SCP_PLATFORM        ?= "invalid"
SCP_COMPILER        ?= "arm-none-eabi"
SCP_LOG_LEVEL       ?= "WARN"

INHIBIT_DEFAULT_DEPS = "1"
DEPENDS = "virtual/arm-none-eabi-gcc-native"
# For now we only build with GCC, so stop meta-clang trying to get involved
TOOLCHAIN = "gcc"

SCP_BUILD_STR = "${@bb.utils.contains('SCP_BUILD_RELEASE', '1', 'release', 'debug', d)}"

inherit deploy

B = "${WORKDIR}/build"
S = "${WORKDIR}/git"

# Allow platform specific copying of only scp or both scp & mcp, default to both
FW_TARGETS ?= "scp mcp"
FW_INSTALL ?= "ramfw romfw"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE ?= "invalid"

LDFLAGS[unexport] = "1"

# No configure
do_configure[noexec] = "1"

EXTRA_OEMAKE = "V=1 \
                BUILD_PATH='${B}' \
                PRODUCT='${SCP_PLATFORM}' \
                MODE='${SCP_BUILD_STR}' \
                LOG_LEVEL='${SCP_LOG_LEVEL}' \
                CC='${SCP_COMPILER}-gcc' \
                AR='${SCP_COMPILER}-ar' \
                SIZE='${SCP_COMPILER}-size' \
                OBJCOPY='${SCP_COMPILER}-objcopy' \
                "

do_compile() {
    oe_runmake -C "${S}"
}
do_compile[cleandirs] += "${B}"

do_install() {
     install -d ${D}/firmware
     for FW in ${FW_TARGETS}; do
        for TYPE in ${FW_INSTALL}; do
           install -D "${B}/product/${SCP_PLATFORM}/${FW}_${TYPE}/${SCP_BUILD_STR}/bin/${FW}_${TYPE}.bin" "${D}/firmware/"
           install -D "${B}/product/${SCP_PLATFORM}/${FW}_${TYPE}/${SCP_BUILD_STR}/bin/${FW}_${TYPE}.elf" "${D}/firmware/"
        done
     done
}

FILES:${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"

FILES:${PN}-dbg += "/firmware/*.elf"
# Skip QA check for relocations in .text of elf binaries
INSANE_SKIP:${PN}-dbg = "arch textrel"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

do_deploy() {
    # Copy the images to deploy directory
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}
addtask deploy after do_install
