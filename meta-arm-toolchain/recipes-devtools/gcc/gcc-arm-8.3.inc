require recipes-devtools/gcc/gcc-common.inc

BASEPV = "8.3"
PV = "arm-${BASEPV}"
CVE_VERSION = "${BASEPV}"

MMYY = "19.03"
RELEASE = "20${MMYY}"
PR = "r${RELEASE}"
BINV = "${BASEPV}.0"

# CVE-2019-15847 is only relevant to POWER9 architecture
CVE_CHECK_WHITELIST += "CVE-2019-15847"

# CVE-2021-37322 is in binutils < 2.32, not in gcc
CVE_CHECK_WHITELIST += "CVE-2021-37322"

FILESEXTRAPATHS =. "${FILE_DIRNAME}/gcc-${BASEPV}:${FILE_DIRNAME}/gcc-${BASEPV}/backport:"

DEPENDS =+ "mpfr gmp libmpc zlib flex-native"
NATIVEDEPS = "mpfr-native gmp-native libmpc-native zlib-native flex-native"

LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

LIC_FILES_CHKSUM = "\
    file://COPYING;md5=59530bdf33659b29e73d4adb9f9f6552 \
    file://COPYING3;md5=d32239bcb673463ab874e80d47fae504 \
    file://COPYING3.LIB;md5=6a6a8e020838b23406c81b19c1d46df6 \
    file://COPYING.LIB;md5=2d5025d4aa3495befef8f17206a5b0a1 \
    file://COPYING.RUNTIME;md5=fe60d87048567d4fe8c8a0ed2448bcc8 \
"

#BASEURI ?= "${GNU_MIRROR}/gcc/gcc-${PV}/gcc-${PV}.tar.bz2"
SRCREV = "47335befa47297ab810945cece69c466417a95c1"
BASEURI ?= "git://git.linaro.org/toolchain/gcc.git;protocol=https;branch=linaro-local/ARM/arm-8-branch"

SRC_URI = "\
           ${BASEURI} \
           file://0001-gcc-4.3.1-ARCH_FLAGS_FOR_TARGET.patch \
           file://0002-gcc-poison-system-directories.patch \
           file://0003-gcc-4.3.3-SYSROOT_CFLAGS_FOR_TARGET.patch \
           file://0004-64-bit-multilib-hack.patch \
           file://0005-optional-libstdc.patch \
           file://0006-gcc-disable-MASK_RELAX_PIC_CALLS-bit.patch \
           file://0007-COLLECT_GCC_OPTIONS.patch \
           file://0008-Use-the-defaults.h-in-B-instead-of-S-and-t-oe-in-B.patch \
           file://0009-fortran-cross-compile-hack.patch \
           file://0010-cpp-honor-sysroot.patch \
           file://0011-MIPS64-Default-to-N64-ABI.patch \
           file://0012-Define-GLIBC_DYNAMIC_LINKER-and-UCLIBC_DYNAMIC_LINKE.patch \
           file://0013-gcc-Fix-argument-list-too-long-error.patch \
           file://0014-Disable-sdt.patch \
           file://0015-libtool.patch \
           file://0016-gcc-armv4-pass-fix-v4bx-to-linker-to-support-EABI.patch \
           file://0017-Use-the-multilib-config-files-from-B-instead-of-usin.patch \
           file://0018-Avoid-using-libdir-from-.la-which-usually-points-to-.patch \
           file://0019-export-CPP.patch \
           file://0020-Disable-the-MULTILIB_OSDIRNAMES-and-other-multilib-o.patch \
           file://0021-Ensure-target-gcc-headers-can-be-included.patch \
           file://0022-gcc-4.8-won-t-build-with-disable-dependency-tracking.patch \
           file://0023-Don-t-search-host-directory-during-relink-if-inst_pr.patch \
           file://0024-Use-SYSTEMLIBS_DIR-replacement-instead-of-hardcoding.patch \
           file://0025-aarch64-Add-support-for-musl-ldso.patch \
           file://0026-libcc1-fix-libcc1-s-install-path-and-rpath.patch \
           file://0027-handle-sysroot-support-for-nativesdk-gcc.patch \
           file://0028-Search-target-sysroot-gcc-version-specific-dirs-with.patch \
           file://0029-Fix-various-_FOR_BUILD-and-related-variables.patch \
           file://0030-nios2-Define-MUSL_DYNAMIC_LINKER.patch \
           file://0031-Add-ssp_nonshared-to-link-commandline-for-musl-targe.patch \
           file://0032-libgcc-Add-knob-to-use-ldbl-128-on-ppc.patch \
           file://0033-Link-libgcc-using-LDFLAGS-not-just-SHLIB_LDFLAGS.patch \
           file://0034-libgcc_s-Use-alias-for-__cpu_indicator_init-instead-.patch \
           file://0035-sync-gcc-stddef.h-with-musl.patch \
           file://0036-fix-segmentation-fault-in-precompiled-header-generat.patch \
           file://0037-Fix-for-testsuite-failure.patch \
           file://0038-Re-introduce-spe-commandline-options.patch \
           file://0039-riscv-Disable-multilib-for-OE.patch \
           file://0040-powerpc-powerpc64-Add-support-for-musl-ldso.patch \
           ${BACKPORTS} \
"
BACKPORTS = "\
"

S = "${TMPDIR}/work-shared/gcc-${PV}-${PR}/git"
#S = "${TMPDIR}/work-shared/gcc-${PV}-${PR}/gcc-${PV}"
#S = "${TMPDIR}/work-shared/gcc-${PV}-${PR}/git"
#S = "${TMPDIR}/work-shared/gcc-${PV}-${PR}/gcc-${RELEASE}"
B = "${WORKDIR}/gcc-${PV}/build.${HOST_SYS}.${TARGET_SYS}"

# Language Overrides
FORTRAN = ""
JAVA = ""

LTO = "--enable-lto"
SSP ?= "--disable-libssp"
SSP_mingw32 = "--enable-libssp"

EXTRA_OECONF_BASE = "\
    ${LTO} \
    ${SSP} \
    --enable-libitm \
    --disable-bootstrap \
    --disable-libmudflap \
    --with-system-zlib \
    ${@'--with-linker-hash-style=${LINKER_HASH_STYLE}' if '${LINKER_HASH_STYLE}' else ''} \
    --enable-linker-build-id \
    --with-ppl=no \
    --with-cloog=no \
    --enable-checking=release \
    --enable-cheaders=c_global \
    --without-isl \
"

EXTRA_OECONF_append_aarchilp32 = " --with-abi=ilp32"

EXTRA_OECONF_PATHS = "\
    --with-gxx-include-dir=/not/exist{target_includedir}/c++/${BINV} \
    --with-sysroot=/not/exist \
    --with-build-sysroot=${STAGING_DIR_TARGET} \
"
