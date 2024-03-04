SUMMARY = "RMM Firmware"
DESCRIPTION = "RMM Firmware for Arm reference platforms"
LICENSE = "BSD-3-Clause & MIT"

SRC_URI = "${SRC_URI_RMM};name=rmm;branch=${SRCBRANCH_rmm} \
	   file://0001-CMakeLists-Add-repositories-for-system-includes.patch \
	"

LIC_FILES_CHKSUM += "file://${WORKDIR}/git/docs/about/license.rst;md5=1375c7c641558198ffe401c2a799d79b"

inherit deploy

DEPENDS += "cmake-native"

RMM_CONFIG ?= "qemu_virt_defcfg"

PACKAGE_ARCH = "${MACHINE_ARCH}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

# Build for debug (set RMM_DEBUG to 1 to activate)
RMM_DEBUG ?= "0"
RMM_BUILD_MODE ?= "${@bb.utils.contains('RMM_DEBUG', '1', 'Debug', 'Release', d)}"

# Handle RMM_DEBUG parameter
EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=${RMM_BUILD_MODE}"
EXTRA_OECMAKE += "-DRMM_CONFIG=${RMM_CONFIG}"

export CROSS_COMPILE="${TARGET_PREFIX}"
export CMAKE_BUILD_PARALLEL_LEVEL = "${@oe.utils.parallel_make(d, False)}"

do_configure[cleandirs] = "${B}"
do_configure() {
    cmake -S ${S} -B ${B} ${EXTRA_OECMAKE}
}

do_compile() {
    cmake --build ${B}
}

do_install() {
    install -d -m 755 ${D}/firmware
    install -m 0644 ${B}/${RMM_BUILD_MODE}/* ${D}/firmware/
}

FILES:${PN} = "/firmware"
SYSROOT_DIRS += "/firmware"

do_deploy() {
    cp -rf ${D}/firmware/* ${DEPLOYDIR}/
}

addtask deploy after do_install
