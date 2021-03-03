SUMMARY = "OpenCSD - An open source CoreSight(tm) Trace Decode library"
HOMEPAGE = "https://github.com/Linaro/OpenCSD"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=ad8cb685eb324d2fa2530b985a43f3e5"

SRC_URI = "git://github.com/Linaro/OpenCSD;protocol=https;branch=master \
           file://0001-build-Fix-build-race-issue-32-reported-on-github.patch"

SRCREV = "957d18219d162f52ebe2426f32a4263ec10f357d"

S = "${WORKDIR}/git"

COMPATIBLE_HOST = "(i.86|x86_64|arm|aarch64).*-linux"

EXTRA_OEMAKE = "ARCH='${TARGET_ARCH}' \
                CROSS_COMPILE='${TARGET_SYS}-' \
                CC='${CC}' \
                CXX='${CXX}' \
                LIB='${AR}' \
                LINKER='${CXX}' \
                LINUX64=1 \
                DEBUG=1 \
                "

do_compile() {
    oe_runmake -C ${S}/decoder/build/linux ${EXTRA_OEMAKE}
}

do_install() {
    oe_runmake \
        PREFIX=${D}/usr \
        INSTALL_BIN_DIR=${D}/${bindir} \
        INSTALL_INCLUDE_DIR=${D}/${includedir} \
        INSTALL_LIB_DIR=${D}/${libdir} \
        -C ${S}/decoder/build/linux install
}

BBCLASSEXTEND = "native"
