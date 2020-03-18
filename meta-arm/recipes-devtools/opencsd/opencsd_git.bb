SUMMARY = "OpenCSD - An open source CoreSight(tm) Trace Decode library"
HOMEPAGE = "https://github.com/Linaro/OpenCSD"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=ad8cb685eb324d2fa2530b985a43f3e5"

SRC_URI = "git://github.com/Linaro/OpenCSD;protocol=http;branch=master"
SRCREV = "03c194117971e4ad0598df29395757ced2e6e9bd"

S = "${WORKDIR}/git"

COMPATIBLE_HOST = "(x86_64.*|aarch64.*)-linux"

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
    oe_runmake -C ${S}/decoder/build/linux PREFIX=${D}/usr install
}

BBCLASSEXTEND = "native"
