# SPDX-License-Identifier: MIT
#
# Copyright (c) 2019 Arm Limited
#

# Recipe for fetching and installing the prebuilt gcc-arm toolchain for
# bare-metal targets.
# Recipe based on the meta-ti layer:
# http://git.yoctoproject.org/cgit/cgit.cgi/meta-ti/tree/recipes-ti/devtools/gcc-arm-none-eabi-native_4.9.2015q3.bb?h=master
#
# Whilst most of the tools built in relies on the linaro-provided
# toolchain, some recipes require the baremetal Arm GCC toolchain. The baremetal
# Arm GCC toolchain is distributed as precompiled binaries. This recipe fetches
# the toolchain and installs it in sysroot.
# Recipes may then 'DEPENDS' on this recipe to fetch the toolchain, making the
# toolchain available in the staging directory of the depending recipe.

GCC_ARM_VERSION = "gcc-arm-none-eabi-7-2018-q2-update"
LICENSE="GPLv3"
LIC_FILES_CHKSUM = "file://share/doc/gcc-arm-none-eabi/license.txt;md5=f77466c63f5787f4bd669c402aabe061"

inherit native

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/${GCC_ARM_VERSION}-linux.tar.bz2;name=tc32"
SRC_URI[tc32.md5sum] = "299ebd3f1c2c90930d28ab82e5d8d6c0"

S = "${WORKDIR}/${GCC_ARM_VERSION}"

do_install() {
    install -d ${D}${INSTALL_GCC_ARM_NONE_EABI}
    cp -r ${S}/. ${D}${INSTALL_GCC_ARM_NONE_EABI}
}

FILES_${PN} = "${INSTALL_GCC_ARM_NONE_EABI}/"

INSANE_SKIP_${PN} = "already-stripped"
