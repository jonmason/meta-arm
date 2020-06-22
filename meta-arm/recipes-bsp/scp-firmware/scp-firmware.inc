SUMMARY = "SCP and MCP Firmware"

PROVIDES += "virtual/control-processor-firmware"

SCP_BUILD_RELEASE   ?= "1"
SCP_COMPILE_VERBOSE ?= "0"
SCP_PLATFORM        ?= "invalid"
SCP_COMPILER        ?= "arm-none-eabi"
SCP_LOG_LEVEL       ?= "WARN"

DEPENDS += "virtual/arm-none-eabi-gcc-native"

SCP_BUILD_STR = "${@bb.utils.contains('SCP_BUILD_RELEASE', '1', 'release', 'debug', d)}"
SCP_COMP_STR  = "${@bb.utils.contains('SCP_COMPILE_VERBOSE', '0', '', 'V=1', d)}"

inherit python3native
inherit deploy

B = "${WORKDIR}/build"
S = "${WORKDIR}/src"

# Allow platform specific copying of only scp or both scp & mcp, default to both
FW_TARGETS ?= "scp mcp"

COMPATIBLE_MACHINE ?= "invalid"

LDFLAGS[unexport] = "1"

# The gcc-arm-none-eabi version does not support -fmacro-prefix-max
DEBUG_PREFIX_MAP_pn-scp = "\
    -fdebug-prefix-map=${WORKDIR}=/usr/src/debug/${PN}/${EXTENDPE}${PV}-${PR} \
    -fdebug-prefix-map=${STAGING_DIR_HOST}= \
    -fdebug-prefix-map=${STAGING_DIR_NATIVE}= \
"

# No configure
do_configure[noexec] = "1"

EXTRA_OEMAKE = "${SCP_COMP_STR} \
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
    oe_runmake -C "${S}" ${EXTRA_OEMAKE}
}
do_compile[cleandirs] += "${B}"

do_install() {
     install -d ${D}/firmware
     for FW in ${FW_TARGETS}; do
        for TYPE in ramfw romfw; do
           install -D "${B}/product/${SCP_PLATFORM}/${FW}_${TYPE}/release/bin/${FW}_${TYPE}.bin" "${D}/firmware/"
        done
     done
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
