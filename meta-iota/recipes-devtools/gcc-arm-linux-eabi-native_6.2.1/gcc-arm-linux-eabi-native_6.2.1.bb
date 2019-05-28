# Recipe for fetching and installing the prebuilt gcc-arm
# linaro 6.2.1 toolchain.
# Recipe based on the meta-ti layer:
# http://git.yoctoproject.org/cgit/cgit.cgi/meta-ti/tree/recipes-ti/devtools/gcc-arm-none-eabi-native_4.9.2015q3.bb?h=master
#
# Linaro 6.2.1 is the recommended toolchain for arm-trusted-firmware


GCC_ARM_VERSION = "gcc-linaro-6.2.1-2016.11-x86_64_arm-linux-gnueabihf"
LICENSE="GPLv3"
LIC_FILES_CHKSUM = "file://share/doc/gdb/gdb/Free-Software.html;md5=96c83aa6efb937afca4e4b5810f2b975"

inherit native

SRC_URI = "https://releases.linaro.org/components/toolchain/binaries/6.2-2016.11/arm-linux-gnueabihf/${GCC_ARM_VERSION}.tar.xz"
SRC_URI[md5sum] = "8f5c112ab5fa26248eb5d9110a09e030"

S = "${WORKDIR}/${GCC_ARM_VERSION}"

do_install() {
    install -d ${D}${INSTALL_GCC_ARM_LINUX_GNUEABIHF}
    cp -r ${S}/. ${D}${INSTALL_GCC_ARM_LINUX_GNUEABIHF}
}


FILES_${PN} = "${INSTALL_GCC_ARM_LINUX_GNUEABIHF}/"
INHIBIT_SYSROOT_STRIP = "1"

INSANE_SKIP_${PN} = "already-stripped"
