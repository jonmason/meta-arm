SUMMARY = "GN is a meta-build system that generates build files for Ninja"
DEPENDS += "ninja-native"

LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=0fca02217a5d49a14dfe2d11837bb34d"

SRC_URI = "git://gn.googlesource.com/gn;protocol=https;branch=main"
SRCREV = "69ec4fca1fa69ddadae13f9e6b7507efa0675263"
PV = "0+git${SRCPV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

# TODO: os map like meson. mingw32 -> mingw

# Currently fails to build with clang, eg:
# https://errors.yoctoproject.org/Errors/Details/610602/
# https://errors.yoctoproject.org/Errors/Details/610486/
TOOLCHAIN = "gcc"

do_configure[cleandirs] += "${B}"
do_configure() {
    python3 ${S}/build/gen.py \
        --platform=${TARGET_OS} \
        --host=${HOST_OS} \
        --out-path=${B} \
        --no-strip
}

do_compile() {
    ninja -C ${B} --verbose
}

do_install() {
    install -d ${D}${bindir}
    install ${B}/gn ${D}${bindir}
}

BBCLASSEXTEND = "native nativesdk"
