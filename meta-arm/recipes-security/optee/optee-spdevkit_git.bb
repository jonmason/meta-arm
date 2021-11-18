SUMMARY = "OP-TEE Secure Partion Development Kit"
DESCRIPTION = "Open Portable Trusted Execution Environment - Development Kit to run secure partitions"
HOMEPAGE = "https://www.op-tee.org/"

LICENSE = "BSD-2-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=c1f21c4f72f372ef38a5a4aee55ec173"

inherit deploy python3native
require optee.inc

CVE_PRODUCT = "linaro:op-tee op-tee:op-tee_os"

DEPENDS = "python3-pycryptodome-native python3-pycryptodomex-native python3-pyelftools-native"

DEPENDS:append:toolchain-clang = " compiler-rt"

SRC_URI = "git://github.com/OP-TEE/optee_os.git;branch=master;protocol=https"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

EXTRA_OEMAKE += " \
    PLATFORM=${OPTEEMACHINE} \
    CFG_${OPTEE_CORE}_core=y \
    CROSS_COMPILE_core=${HOST_PREFIX} \
    CROSS_COMPILE_sp_${OPTEE_ARCH}=${HOST_PREFIX} \
    CFG_CORE_FFA=y \
    CFG_WITH_SP=y \
    O=${B} \
"

CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
CPPFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

do_configure[noexec] = "1"

do_compile() {
    oe_runmake -C ${S} sp_dev_kit
}
do_compile[cleandirs] = "${B}"

do_install() {
    #install SP devkit
    install -d ${D}${includedir}/optee/export-user_sp/
    for f in ${B}/export-sp_${OPTEE_ARCH}/* ; do
        cp -aR $f ${D}${includedir}/optee/export-user_sp/
    done
    cat > ${D}${includedir}/optee/export-user_sp/include/stddef.h <<'EOF'
#ifndef STDDEF_H
#define STDDEF_H

#include <stddef_.h>

#ifndef _PTRDIFF_T
typedef long ptrdiff_t;
#define _PTRDIFF_T
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define offsetof(st, m) __builtin_offsetof(st, m)

#endif /* STDDEF_H */
EOF
    cat > ${D}${includedir}/optee/export-user_sp/include/stddef_.h <<'EOF'
#ifndef STDDEF__H
#define STDDEF__H

#ifndef SIZET_
typedef unsigned long size_t;
#define SIZET_
#endif

#endif /* STDDEF__H */
EOF
    cat > ${D}${includedir}/optee/export-user_sp/include/stdarg.h <<'EOF'
#ifndef STDARG_H
#define STDARG_H

#define va_list __builtin_va_list
#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_end(ap) __builtin_va_end(ap)
#define va_copy(to, from) __builtin_va_copy(to, from)
#define va_arg(to, type) __builtin_va_arg(to, type)

#endif /* STDARG_H */
EOF
    cat > ${D}${includedir}/optee/export-user_sp/include/stdbool.h <<'EOF'
#ifndef STDBOOL_H
#define STDBOOL_H

#define bool	_Bool

#define true	1
#define false	0

#define __bool_true_false_are_defined	1

#endif /* STDBOOL_H */
EOF
}

PACKAGE_ARCH = "${MACHINE_ARCH}"

# optee-spdevkit static library is part of optee-os image. No need to package this library in a staticdev package
INSANE_SKIP:${PN}-dev = "staticdev"
