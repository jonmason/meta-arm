require recipes-bsp/uefi/edk2-firmware_202508.bb
PROVIDES:remove = "virtual/bootloader"

LICENSE += "& Apache-2.0"
LIC_FILES_CHKSUM += "file://ShellPkg/Application/sysarch-acs/LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRC_URI += "git://github.com/ARM-software/sysarch-acs.git;destsuffix=edk2/ShellPkg/Application/sysarch-acs;protocol=https;branch=main;name=acs \
            git://github.com/tianocore/edk2-libc;destsuffix=edk2/edk2-libc;protocol=https;branch=master;name=libc \
            file://edk2_sbsa.patch \
            file://hacking.patch;patchdir=ShellPkg/Application/sysarch-acs \
            "

# v25.07_REL7.2.3 tag
SRCREV_acs = "5010532345a3ef82d9069171486258896a56a84c"
# v3.6.8.1 tag
SRCREV_libc = "caea801aac338aa60f85a7c10148ca0b4440fff3"

UPSTREAM_CHECK_URI = "https://github.com/ARM-software/sysarch-acs/releases"

# FIXME - some weirdness here with clang.  Looks like there are some
# hardcoded assembly instructions which need feature enablement that
# magically happens in gcc, but needs explicit enablement in clang.
# Hardcode GCC until this can be bottomed out.
TOOLCHAIN:aarch64 = "gcc"

COMPATIBLE_HOST = "aarch64.*-linux"
COMPATIBLE_MACHINE = ""
PACKAGE_ARCH = "${TUNE_PKGARCH}"

EDK2_PLATFORM = "Shell"
EDK2_PLATFORM_DSC = "ShellPkg/ShellPkg.dsc"
EDK2_EXTRA_BUILD = "--module ShellPkg/Application/sysarch-acs/apps/uefi/Sbsa.inf"

export ACS_PATH = "${S}/ShellPkg/Application/sysarch-acs"
PACKAGES_PATH .= ":${S}/edk2-libc"

#do_patch() {
#    cd ${UNPACKDIR}/edk2/
#    patch -p1 < ${S}/ShellPkg/Application/sysarch-acs/patches/edk2_sbsa.patch
#}

do_install() {
    install -d ${D}/firmware
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/*/Sbsa.efi ${D}/firmware/
}
