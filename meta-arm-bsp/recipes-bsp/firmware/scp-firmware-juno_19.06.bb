DESCRIPTION = "System Control Processor (SCP) firmware for Juno"
HOMEPAGE = "https://github.com/ARM-software/SCP-firmware"
LICENSE = "BSD-3-Clause"
SECTION = "firmware"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "juno"

PROVIDES += "virtual/scp-firmware"

# For now, for juno we retrieve the SCP firmware in binary format
# from Linaro Releases.
SRC_URI = "http://releases.linaro.org/members/arm/platforms/${PV}/juno-latest-oe-uboot.zip;subdir=${UNPACK_DIR}"

SRC_URI[md5sum] = "01b662b81fa409d55ff298238ad24003"
SRC_URI[sha256sum] = "b8a3909bb3bc4350a8771b863193a3e33b358e2a727624a77c9ecf13516cec82"

UNPACK_DIR = "juno-firmware"

S = "${WORKDIR}/${UNPACK_DIR}"

SCP_FIRMWARE_BINARIES = "scp_bl1.bin scp_bl2.bin"

inherit nopackages

do_configure[noexec] = "1"
do_configure[compile] = "1"

do_install() {
    install -d ${D}/firmware
    for file in ${SCP_FIRMWARE_BINARIES}; do
        install -m 644 ${S}/SOFTWARE/${file} ${D}/firmware
    done
}

SYSROOT_DIRS += "/firmware"
