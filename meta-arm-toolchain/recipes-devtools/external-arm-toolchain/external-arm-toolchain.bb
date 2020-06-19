require recipes-core/glibc/glibc-package.inc

require license.inc

INHIBIT_DEFAULT_DEPS = "1"

LIC_FILES_CHKSUM = "\
	file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
	file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420 \
"

PROVIDES += "\
	linux-libc-headers \
	virtual/${TARGET_PREFIX}gcc \
	virtual/${TARGET_PREFIX}g++ \
	virtual/${TARGET_PREFIX}gcc-initial \
	virtual/${TARGET_PREFIX}binutils \
	virtual/${TARGET_PREFIX}libc-for-gcc \
	virtual/${TARGET_PREFIX}compilerlibs \
	virtual/libc \
	virtual/libintl \
	virtual/libiconv \
	virtual/crypt \
	glibc-mtrace \
	glibc-thread-db \
	glibc \
	libc-mtrace \
	gcc-runtime \
	libgcc \
	libg2c \
	libg2c-dev \
	libssp \
	libssp-dev \
	libssp-staticdev \
	libgfortran \
	libgfortran-dev \
	libgfortran-staticdev \
	libmudflap \
	libmudflap-dev \
	libgomp \
	libgomp-dev \
	libgomp-staticdev \
	libitm \
	libitm-dev \
	libitm-staticdev \
	libquadmath \
	libquadmath-dev \
	libquadmath-staticdev \
	virtual/linux-libc-headers \
	libgcov-staticdev \
	virtual/libc-locale \
"

PV = "${EAT_VER_MAIN}"

BINV = "${EAT_VER_GCC}"

SRC_URI = "file://SUPPORTED"

do_install() {
	# Add stubs for files OE-core expects
	install -d ${S}/nscd/
	touch  ${S}/nscd/nscd.init
	touch  ${S}/nscd/nscd.conf
	touch  ${S}/nscd/nscd.service
	touch  ${S}/../makedbs.sh

	install -d ${D}${base_libdir}
	install -d ${D}${base_sbindir}
	install -d ${D}${bindir}
	install -d ${D}${sbindir}
	install -d ${D}${libdir}
	install -d ${D}${libexecdir}
	install -d ${D}${datadir}
	install -d ${D}${includedir}
	install -d ${D}/include
	install -d ${D}${libdir}/${TARGET_SYS}/${EAT_VER_GCC}
	install -d ${D}${libdir}/gcc/${TARGET_SYS}/${EAT_VER_GCC}

	CP_ARGS="-Prf --preserve=mode,timestamps --no-preserve=ownership"
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/${EAT_LIBDIR}/*  ${D}${base_libdir}
	if [ -d ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/${EAT_LIBDIR}/${EAT_TARGET_SYS} ]; then
		cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/${EAT_LIBDIR}/${EAT_TARGET_SYS}/*  ${D}${base_libdir}
	else
		if [ -f ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/${EAT_LIBDIR}/ld-${EAT_VER_LIBC}.so ]; then
			cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/${EAT_LIBDIR}/*  ${D}${base_libdir}
		else
			cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/${EAT_LIBDIR}/*.so*  ${D}${base_libdir}
		fi
	fi
	if [ -d ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/${EAT_LIBDIR}/${EAT_TARGET_SYS} ]; then
		cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/${EAT_LIBDIR}/${EAT_TARGET_SYS}/*  ${D}${libdir}
	else
		cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/${EAT_LIBDIR}/*  ${D}${libdir}
		if [ ! -f ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/${EAT_LIBDIR}/ld-${EAT_VER_LIBC}.so ]; then
			rm -rf ${D}${libdir}/*.so*
		fi
	fi
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/share/*  ${D}${datadir}
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/include/*  ${D}${includedir}
	if [ -d ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/include/${EAT_TARGET_SYS} ]; then
		cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/include/${EAT_TARGET_SYS}/*  ${D}${includedir}
		rm -r ${D}${includedir}/${EAT_TARGET_SYS}
	fi

	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/include/* ${D}${includedir}
	if [ -d ${D}${includedir}/c++/${EAT_VER_GCC}/${EAT_TARGET_SYS} ]; then
		mv ${D}${includedir}/c++/${EAT_VER_GCC}/${EAT_TARGET_SYS} ${D}${includedir}/c++/${EAT_VER_GCC}/${TARGET_SYS}
	fi
	ln -sf ../usr/include/c++ ${D}/include/c++

	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/bin/* ${D}${bindir}
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/usr/sbin/* ${D}${sbindir}
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/${EAT_TARGET_SYS}/libc/sbin/* ${D}${base_sbindir}
	rm -rf ${D}${bindir}/gdbserver
	sed -i -e 's#/arm/tools/gnu/bash/4.2/rhe6-x86_64##' ${D}${bindir}/tzselect
	sed -i -e 's#/arm/tools/gnu/bash/4.2/rhe6-x86_64##' ${D}${bindir}/ldd
	sed -i -e 's#/bin/bash#/bin/sh#' ${D}${bindir}/tzselect
	sed -i -e 's#/bin/bash#/bin/sh#' ${D}${bindir}/ldd

	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/lib/gcc/${EAT_TARGET_SYS}/${EAT_VER_GCC}/crt*.o ${D}${libdir}/${TARGET_SYS}/${EAT_VER_GCC}/
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/lib/gcc/${EAT_TARGET_SYS}/${EAT_VER_GCC}/libgcc* ${D}${libdir}/${TARGET_SYS}/${EAT_VER_GCC}/
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/lib/gcc/${EAT_TARGET_SYS}/${EAT_VER_GCC}/libgcov* ${D}${libdir}/gcc/${TARGET_SYS}/${EAT_VER_GCC}/
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/lib/gcc/${EAT_TARGET_SYS}/${EAT_VER_GCC}/include ${D}${libdir}/gcc/${TARGET_SYS}/${EAT_VER_GCC}/
	cp ${CP_ARGS} ${EXTERNAL_TOOLCHAIN}/lib/gcc/${EAT_TARGET_SYS}/${EAT_VER_GCC}/finclude ${D}${libdir}/gcc/${TARGET_SYS}/${EAT_VER_GCC}/

	# fix up the copied symlinks (they are still pointing to the multiarch directory)
	linker_name="${@bb.utils.contains("TUNE_FEATURES", "aarch64", "ld-linux-aarch64.so.1", bb.utils.contains("TUNE_FEATURES", "callconvention-hard", "ld-linux-armhf.so.3", "ld-linux.so.3",d), d)}"
	ln -sf ld-${EAT_VER_LIBC}.so ${D}${base_libdir}/${linker_name}
	ln -sf ../../lib/librt.so.1 ${D}${libdir}/librt.so
	ln -sf ../../lib/libcrypt.so.1 ${D}${libdir}/libcrypt.so
	ln -sf ../../lib/libresolv.so.2 ${D}${libdir}/libresolv.so
	ln -sf ../../lib/libnss_hesiod.so.2 ${D}${libdir}/libnss_hesiod.so
	ln -sf ../../lib/libutil.so.1 ${D}${libdir}/libutil.so
	ln -sf ../../lib/libBrokenLocale.so.1 ${D}${libdir}/libBrokenLocale.so
	ln -sf ../../lib/libpthread.so.0 ${D}${libdir}/libpthread.so
	ln -sf ../../lib/libthread_db.so.1 ${D}${libdir}/libthread_db.so
	ln -sf ../../lib/libanl.so.1 ${D}${libdir}/libanl.so
	ln -sf ../../lib/libdl.so.2 ${D}${libdir}/libdl.so
	ln -sf ../../lib/libnss_db.so.2 ${D}${libdir}/libnss_db.so
	ln -sf ../../lib/libnss_dns.so.2 ${D}${libdir}/libnss_dns.so
	ln -sf ../../lib/libnss_files.so.2 ${D}${libdir}/libnss_files.so
	ln -sf ../../lib/libnss_compat.so.2 ${D}${libdir}/libnss_compat.so
	ln -sf ../../lib/libm.so.6 ${D}${libdir}/libm.so

	# remove potential .so duplicates from base_libdir
	# for all symlinks created above in libdir
	rm -f ${D}${base_libdir}/librt.so
	rm -f ${D}${base_libdir}/libcrypt.so
	rm -f ${D}${base_libdir}/libresolv.so
	rm -f ${D}${base_libdir}/libnss_hesiod.so
	rm -f ${D}${base_libdir}/libutil.so
	rm -f ${D}${base_libdir}/libBrokenLocale.so
	rm -f ${D}${base_libdir}/libpthread.so
	rm -f ${D}${base_libdir}/libthread_db.so
	rm -f ${D}${base_libdir}/libanl.so
	rm -f ${D}${base_libdir}/libdl.so
	rm -f ${D}${base_libdir}/libnss_db.so
	rm -f ${D}${base_libdir}/libnss_dns.so
	rm -f ${D}${base_libdir}/libnss_files.so
	rm -f ${D}${base_libdir}/libnss_compat.so
	rm -f ${D}${base_libdir}/libm.so

	# Move these completely to ${libdir} and delete duplicates in ${base_libdir}
	for lib in asan atomic gfortran gomp itm lsan sanitizer stdc++ tsan ubsan; do
		if [ -e ${D}${base_libdir}/lib${lib}.spec ] ; then
			mv ${D}${base_libdir}/lib${lib}.spec ${D}${libdir}
		fi
		if [ -e ${D}${base_libdir}/lib${lib}.a ] ; then
			mv ${D}${base_libdir}/lib${lib}.a ${D}${libdir}
		fi
		rm -f ${D}${base_libdir}/lib${lib}*
	done

	# Clean up duplicate libs that are both in base_libdir and libdir
	rm -f ${D}${libdir}/libgcc*

	# Besides ld-${EAT_VER_LIBC}.so, other libs can have duplicates like lib*-${EAT_VER_LIBC}.so
	# Only remove them if both are regular files and are identical
	for i in ${D}${base_libdir}/lib*-${EAT_VER_LIBC}.so; do
		f=$(echo $i | sed 's/-${EAT_VER_LIBC}//')
		l=$(ls $f.*)
		if [ $(readlink -f $i ) = $l ]; then
			echo "$i is a symlink of $l, keep it"
		elif [ $(readlink -f $l ) = $i ]; then
			echo "$l is a symlink of $i, keep it"
		else
			cmp -s $i $l
			if [ $? -eq 0 ]; then
				echo "$i is a duplicate of $l, remove it"
				rm $i
			else
				echo "$i and $l are different files, keep them both"
			fi
		fi
	done

	if [ -d ${D}${base_libdir}/arm-linux-gnueabi ]; then
	   rm -rf ${D}${base_libdir}/arm-linux-gnueabi
	fi

	if [ -d ${D}${base_libdir}/ldscripts ]; then
	   rm -rf ${D}${base_libdir}/ldscripts
	fi

	# Provided by libnsl2
	rm -rf ${D}${includedir}/rpcsvc/yppasswd.*
	# Provided by quota
	rm -rf ${D}${includedir}/rpcsvc/rquota.*

	if [ -f ${D}${libdir}/libc.so ];then
		sed -i -e "s# /${EAT_LIBDIR}/${EAT_TARGET_SYS}# ../../${EAT_LIBDIR}#g" -e "s# /usr/${EAT_LIBDIR}/# /usr/lib/#g" -e "s# /usr/${EAT_LIBDIR}/${EAT_TARGET_SYS}# .#g" -e "s# /${EAT_LIBDIR}/ld-linux# ../../${EAT_LIBDIR}/ld-linux#g" ${D}${libdir}/libc.so
		sed -i -e "s# /${EAT_LIBDIR}/libc.so.6# /lib/libc.so.6#g" ${D}${libdir}/libc.so
		sed -i -e "s# /lib# ../../lib#g" -e "s# /usr/lib# .#g" ${D}${libdir}/libc.so
	fi

	if [ -f ${D}${base_libdir}/libc.so ];then
		sed -i -e "s# /${EAT_LIBDIR}/${EAT_TARGET_SYS}# ../../lib#g" -e "s# /usr/${EAT_LIBDIR}/${EAT_TARGET_SYS}# .#g" "s# /${EAT_LIBDIR}/# /lib/#g" ${D}${base_libdir}/libc.so
		if [ -f ${D}${base_libdir}/libc.so.6 ]; then
			sed -i -e "s# /usr/${EAT_LIBDIR}/libc.so.6# /lib/libc.so.6#g" "s# /${EAT_LIBDIR}/libc.so.6# /lib/libc.so.6#g" ${D}${base_libdir}/libc.so.6
		fi
	fi

	# Remove if empty
	rmdir ${D}${bindir} || true
	rmdir ${D}${sbindir} || true
	rmdir ${D}${base_sbindir} || true
	rmdir ${D}${libexecdir} || true

	# Remove unused /usr/share/info/dir
	rm -f ${D}${infodir}/dir
}

# External toolchain doesn't provide multilib support so make corresponding
# install API as an empty API to avoid an unnecessary errors.
oe_multilib_header () {
	return
}

PACKAGES_DYNAMIC = "^locale-base-.* \
                    ^glibc-gconv-.* ^glibc-charmap-.* ^glibc-localedata-.* ^glibc-binary-localedata-.* \
                    ^${MLPREFIX}glibc-gconv$"

# PACKAGES is split up according to the 'source' recipes/includes in OE-core
# Stylistic differences are kept to make copy/pasting easier.

# From gcc-runtime.inc

PACKAGES += "\
    gcc-runtime-dbg \
    libstdc++ \
    libstdc++-precompile-dev \
    libstdc++-dev \
    libstdc++-staticdev \
    libg2c \
    libg2c-dev \
    libssp \
    libssp-dev \
    libssp-staticdev \
    libmudflap \
    libmudflap-dev \
    libmudflap-staticdev \
    libquadmath \
    libquadmath-dev \
    libquadmath-staticdev \
    libgomp \
    libgomp-dev \
    libgomp-staticdev \
    libatomic \
    libatomic-dev \
    libatomic-staticdev \
    libitm \
    libitm-dev \
    libitm-staticdev \
"

# From gcc-sanitizers.inc

PACKAGES += "gcc-sanitizers gcc-sanitizers-dbg"
PACKAGES += "libasan libubsan liblsan libtsan"
PACKAGES += "libasan-dev libubsan-dev liblsan-dev libtsan-dev"
PACKAGES += "libasan-staticdev libubsan-staticdev liblsan-staticdev libtsan-staticdev"

# From libgfortran.inc:

PACKAGES += "\
    libgfortran-dbg \
    libgfortran \
    libgfortran-dev \
    libgfortran-staticdev \
"

# libgcc.inc uses ${PN}, so replace that

PACKAGES += "\
    libgcc \
    libgcc-dev \
    libgcc-dbg \
"

# ... and the leftovers

PACKAGES =+ "\
        ${PN}-mtrace \
	libgcov-staticdev \
	linux-libc-headers \
	linux-libc-headers-dev \
"

# Re-order PACKAGES list in order to shift ${PN}-dev towards the end as
# it is meant to pick up remaining dev libraries and headers that aren't
# picked up by other packages. And since some static libraries needs to
# be packaged in ${PN}-dev, so we need to keep ${PN}-staticdev later in
# order.

PACKAGES := "${@oe.utils.str_filter_out('${PN}-dev', '${PACKAGES}', d)}"
PACKAGES := "${@oe.utils.str_filter_out('${PN}-staticdev', '${PACKAGES}', d)}"
PACKAGES += "\
	${PN}-dev \
	${PN}-staticdev \
"

INSANE_SKIP_${PN}-dbg = "staticdev"
INSANE_SKIP_${PN}-utils += "ldflags"
INSANE_SKIP_libstdc++ += "ldflags"
INSANE_SKIP_libgfortran += "ldflags"
INSANE_SKIP_libgcc += "ldflags dev-deps"
INSANE_SKIP_libgcc-dev += "staticdev"
INSANE_SKIP_libgfortran += "ldflags dev-deps"
INSANE_SKIP_libstdc++ += "ldflags dev-deps"
INSANE_SKIP_libatomic += "ldflags"
INSANE_SKIP_libasan += "ldflags"
INSANE_SKIP_libubsan += "ldflags"
INSANE_SKIP_libssp += "ldflags"
INSANE_SKIP_libgomp += "ldflags"
INSANE_SKIP_libitm += "ldflags"
INSANE_SKIP_gdbserver += "ldflags"

# OE-core has literally listed 'glibc' in LIBC_DEPENDENCIES :/
RPROVIDES_${PN} = "glibc rtld(GNU_HASH)"
# Add runtime provides for the other libc* packages as well
RPROVIDES_${PN}-dev = "glibc-dev"
RPROVIDES_${PN}-doc = "glibc-doc"
RPROVIDES_${PN}-dbg = "glibc-dbg"
RPROVIDES_${PN}-pic = "glibc-pic"
RPROVIDES_${PN}-utils = "glibc-utils"
RPROVIDES_${PN}-mtrace = "glibc-mtrace libc-mtrace"

PKG_${PN} = "glibc"
PKG_${PN}-dev = "glibc-dev"
PKG_${PN}-doc = "glibc-doc"
PKG_${PN}-dbg = "glibc-dbg"
PKG_${PN}-pic = "glibc-pic"
PKG_${PN}-utils = "glibc-utils"
PKG_${PN}-mtrace = "glibc-mtrace"
PKG_${PN}-gconv = "glibc-gconv"
PKG_${PN}-extra-nss = "glibc-extra-nss"
PKG_${PN}-thread-db = "glibc-thread-db"
PKG_${PN}-pcprofile = "glibc-pcprofile"
PKG_${PN}-staticdev = "glibc-staticdev"

PKGV = "${EAT_VER_LIBC}"
PKGV_${PN} = "${EAT_VER_LIBC}"
PKGV_${PN}-dev = "${EAT_VER_LIBC}"
PKGV_${PN}-doc = "${EAT_VER_LIBC}"
PKGV_${PN}-dbg = "${EAT_VER_LIBC}"
PKGV_${PN}-pic = "${EAT_VER_LIBC}"
PKGV_${PN}-utils = "${EAT_VER_LIBC}"
PKGV_${PN}-mtrace = "${EAT_VER_LIBC}"
PKGV_${PN}-gconv = "${EAT_VER_LIBC}"
PKGV_${PN}-extra-nss = "${EAT_VER_LIBC}"
PKGV_${PN}-thread-db = "${EAT_VER_LIBC}"
PKGV_${PN}-pcprofile = "${EAT_VER_LIBC}"
PKGV_${PN}-staticdev = "${EAT_VER_LIBC}"
PKGV_catchsegv = "${EAT_VER_LIBC}"
PKGV_glibc-extra-nss = "${EAT_VER_LIBC}"
PKGV_glibc-thread-db = "${EAT_VER_LIBC}"

PKGV_libmemusage = "${EAT_VER_LIBC}"
PKGV_libsegfault = "${EAT_VER_LIBC}"
PKGV_libsotruss = "${EAT_VER_LIBC}"
PKGV_sln = "${EAT_VER_LIBC}"
PKGV_nscd = "${EAT_VER_LIBC}"
PKGV_ldd = "${EAT_VER_LIBC}"

PKGV_libasan-dev = "${EAT_VER_GCC}"
PKGV_libasan = "${EAT_VER_GCC}"
PKGV_libasan-staticdev = "${EAT_VER_GCC}"
PKGV_libatomic-dev = "${EAT_VER_GCC}"
PKGV_libatomic = "${EAT_VER_GCC}"
PKGV_libatomic-staticdev = "${EAT_VER_GCC}"
PKGV_libg2c-dev = "${EAT_VER_GCC}"
PKGV_libg2c = "${EAT_VER_GCC}"
PKGV_libgcc-dev = "${EAT_VER_GCC}"
PKGV_libgcc = "${EAT_VER_GCC}"
PKGV_libgfortran-dbg = "${EAT_VER_GCC}"
PKGV_libgfortran-dev = "${EAT_VER_GCC}"
PKGV_libgfortran = "${EAT_VER_GCC}"
PKGV_libgfortran-staticdev = "${EAT_VER_GCC}"
PKGV_libgomp-dev = "${EAT_VER_GCC}"
PKGV_libgomp = "${EAT_VER_GCC}"
PKGV_libgomp-staticdev = "${EAT_VER_GCC}"
PKGV_libitm-dev = "${EAT_VER_GCC}"
PKGV_libitm = "${EAT_VER_GCC}"
PKGV_libitm-staticdev = "${EAT_VER_GCC}"
PKGV_liblsan-dev = "${EAT_VER_GCC}"
PKGV_liblsan = "${EAT_VER_GCC}"
PKGV_liblsan-staticdev = "${EAT_VER_GCC}"
PKGV_libmudflap-dev = "${EAT_VER_GCC}"
PKGV_libmudflap = "${EAT_VER_GCC}"
PKGV_libmudflap-staticdev = "${EAT_VER_GCC}"
PKGV_libquadmath-dev = "${EAT_VER_GCC}"
PKGV_libquadmath = "${EAT_VER_GCC}"
PKGV_libquadmath-staticdev = "${EAT_VER_GCC}"
PKGV_libssp-dev = "${EAT_VER_GCC}"
PKGV_libssp = "${EAT_VER_GCC}"
PKGV_libssp-staticdev = "${EAT_VER_GCC}"
PKGV_libstdc++-dbg = "${EAT_VER_GCC}"
PKGV_libstdc++-dev = "${EAT_VER_GCC}"
PKGV_libstdc++ = "${EAT_VER_GCC}"
PKGV_libstdc++-precompile-dev = "${EAT_VER_GCC}"
PKGV_libstdc++-staticdev = "${EAT_VER_GCC}"
PKGV_libtsan-dev = "${EAT_VER_GCC}"
PKGV_libtsan = "${EAT_VER_GCC}"
PKGV_libtsan-staticdev = "${EAT_VER_GCC}"
PKGV_libubsan-dev = "${EAT_VER_GCC}"
PKGV_libubsan = "${EAT_VER_GCC}"
PKGV_libubsan-staticdev = "${EAT_VER_GCC}"

PKGV_linux-libc-headers-dev = "${EAT_VER_KERNEL}"
PKGV_linux-libc-headers = "${EAT_VER_KERNEL}"

PKGV_gdbserver = "${EAT_VER_GDBSERVER}"

ALLOW_EMPTY_${PN}-mtrace = "1"
FILES_${PN}-mtrace = "${bindir}/mtrace"

FILES_libgcov-staticdev = "${libdir}/gcc/${TARGET_SYS}/${BINV}/libgcov.a"

FILES_libsegfault = "${base_libdir}/libSegFault*"

FILES_catchsegv = "${bindir}/catchsegv"
RDEPENDS_catchsegv = "libsegfault"

# From libgfortran.inc:

FILES_libgfortran = "${libdir}/libgfortran.so.*"
FILES_libgfortran-dev = "\
    ${libdir}/libgfortran*.so \
    ${libdir}/libgfortran.spec \
    ${libdir}/libgfortran.la \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/libgfortranbegin.* \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/libcaf_single* \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/finclude/ \
"
FILES_libgfortran-staticdev = "${libdir}/libgfortran.a"


# From gcc-sanitizers.inc:

FILES_libasan += "${libdir}/libasan.so.*"
FILES_libasan-dev += "\
    ${libdir}/libasan_preinit.o \
    ${libdir}/libasan.so \
    ${libdir}/libasan.la \
"
FILES_libasan-staticdev += "${libdir}/libasan.a"

FILES_libubsan += "${libdir}/libubsan.so.*"
FILES_libubsan-dev += "\
    ${libdir}/libubsan.so \
    ${libdir}/libubsan.la \
"
FILES_libubsan-staticdev += "${libdir}/libubsan.a"

FILES_liblsan += "${libdir}/liblsan.so.*"
FILES_liblsan-dev += "\
    ${libdir}/liblsan.so \
    ${libdir}/liblsan.la \
    ${libdir}/liblsan_preinit.o \
"
FILES_liblsan-staticdev += "${libdir}/liblsan.a"

FILES_libtsan += "${libdir}/libtsan.so.*"
FILES_libtsan-dev += "\
    ${libdir}/libtsan.so \
    ${libdir}/libtsan.la \
    ${libdir}/libtsan_*.o \
"
FILES_libtsan-staticdev += "${libdir}/libtsan.a"

FILES_gcc-sanitizers = "${libdir}/*.spec ${libdir}/gcc/${TARGET_SYS}/${BINV}/include/sanitizer/*.h"

# From libgcc.inc:

FILES_libgcc = "${base_libdir}/libgcc_s.so.1"

FILES_libgcc-dev = "\
    ${base_libdir}/libgcc*.so \
    ${@oe.utils.conditional('BASETARGET_SYS', '${TARGET_SYS}', '', '${libdir}/${BASETARGET_SYS}', d)} \
    ${libdir}/${TARGET_SYS}/${BINV}* \
    ${libdir}/${TARGET_ARCH}${TARGET_VENDOR}* \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/include \
"

FILES_linux-libc-headers = ""
FILES_linux-libc-headers-dev = "\
	${includedir}/asm* \
	${includedir}/linux \
	${includedir}/mtd \
	${includedir}/rdma \
	${includedir}/scsi \
	${includedir}/sound \
	${includedir}/video \
"
FILES_${PN} += "\
	${libdir}/bin \
	${libdir}/locale \
	${libdir}/gconv/gconv-modules \
	${datadir}/zoneinfo \
	${base_libdir}/libcrypt*.so.* \
	${base_libdir}/libcrypt-*.so \
	${base_libdir}/libc.so.* \
	${base_libdir}/libc-*.so \
	${base_libdir}/libm.so.* \
	${base_libdir}/libmemusage.so \
	${base_libdir}/libm-*.so \
	${base_libdir}/ld*.so.* \
	${base_libdir}/ld-*.so \
	${base_libdir}/libpthread*.so.* \
	${base_libdir}/libpthread*.so \
	${base_libdir}/libpthread-*.so \
	${base_libdir}/libresolv*.so.* \
	${base_libdir}/libresolv-*.so \
	${base_libdir}/librt*.so.* \
	${base_libdir}/librt-*.so \
	${base_libdir}/libutil*.so.* \
	${base_libdir}/libutil-*.so \
	${base_libdir}/libnss_files*.so.* \
	${base_libdir}/libnss_files-*.so \
	${base_libdir}/libnss_compat*.so.* \
	${base_libdir}/libnss_compat-*.so \
	${base_libdir}/libnss_dns*.so.* \
	${base_libdir}/libnss_dns-*.so \
	${base_libdir}/libnss_nis*.so.* \
	${base_libdir}/libnss_nisplus-*.so \
	${base_libdir}/libnss_nisplus*.so.* \
	${base_libdir}/libnss_nis-*.so \
	${base_libdir}/libnss_hesiod*.so.* \
	${base_libdir}/libnss_hesiod-*.so \
	${base_libdir}/libdl*.so.* \
	${base_libdir}/libdl-*.so \
	${base_libdir}/libanl*.so.* \
	${base_libdir}/libanl-*.so \
	${base_libdir}/libBrokenLocale*.so.* \
	${base_libdir}/libBrokenLocale-*.so \
	${base_libdir}/libthread_db*.so.* \
	${base_libdir}/libthread_db-*.so \
	${base_libdir}/libmemusage.so \
	${base_libdir}/libSegFault.so \
	${base_libdir}/libpcprofile.so \
    "

FILES_${PN}-dbg += "${base_libdir}/debug"

# From gcc-runtime.inc

# include python debugging scripts
FILES_gcc-runtime-dbg += "\
    ${libdir}/libstdc++.so.*-gdb.py \
    ${datadir}/gcc-${BINV}/python/libstdcxx \
"

FILES_libg2c = "${target_libdir}/libg2c.so.*"
SUMMARY_libg2c = "Companion runtime library for g77"
FILES_libg2c-dev = "\
    ${libdir}/libg2c.so \
    ${libdir}/libg2c.a \
    ${libdir}/libfrtbegin.a \
"
SUMMARY_libg2c-dev = "Companion runtime library for g77 - development files"

FILES_libstdc++ = "${libdir}/libstdc++.so.*"
SUMMARY_libstdc++ = "GNU standard C++ library"
FILES_libstdc++-dev = "\
    /include/c++ \
    ${includedir}/c++/ \
    ${libdir}/libstdc++.so \
    ${libdir}/libstdc++*.la \
    ${libdir}/libsupc++.la \
"
SUMMARY_libstdc++-dev = "GNU standard C++ library - development files"

FILES_libstdc++-staticdev = "\
    ${libdir}/libstdc++*.a \
    ${libdir}/libsupc++.a \
"
SUMMARY_libstdc++-staticdev = "GNU standard C++ library - static development files"

FILES_libstdc++-precompile-dev = "${includedir}/c++/${TARGET_SYS}/bits/*.gch"
SUMMARY_libstdc++-precompile-dev = "GNU standard C++ library - precompiled header files"

FILES_libssp = "${libdir}/libssp.so.*"
SUMMARY_libssp = "GNU stack smashing protection library"
FILES_libssp-dev = "\
    ${libdir}/libssp*.so \
    ${libdir}/libssp*_nonshared.a \
    ${libdir}/libssp*.la \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/include/ssp \
"
SUMMARY_libssp-dev = "GNU stack smashing protection library - development files"
FILES_libssp-staticdev = "${libdir}/libssp*.a"
SUMMARY_libssp-staticdev = "GNU stack smashing protection library - static development files"

FILES_libquadmath = "${libdir}/libquadmath*.so.*"
SUMMARY_libquadmath = "GNU quad-precision math library"
FILES_libquadmath-dev = "\
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/include/quadmath* \
    ${libdir}/libquadmath*.so \
    ${libdir}/libquadmath.la \
"
SUMMARY_libquadmath-dev = "GNU quad-precision math library - development files"
FILES_libquadmath-staticdev = "${libdir}/libquadmath.a"
SUMMARY_libquadmath-staticdev = "GNU quad-precision math library - static development files"

# NOTE: mudflap has been removed as of gcc 4.9 and has been superseded by the address sanitiser
FILES_libmudflap = "${libdir}/libmudflap*.so.*"
SUMMARY_libmudflap = "Pointer debugging library for gcc"
FILES_libmudflap-dev = "\
    ${libdir}/libmudflap*.so \
    ${libdir}/libmudflap.la \
"
SUMMARY_libmudflap-dev = "Pointer debugging library for gcc - development files"
FILES_libmudflap-staticdev = "${libdir}/libmudflap.a"
SUMMARY_libmudflap-staticdev = "Pointer debugging library for gcc - static development files"

FILES_libgomp = "${libdir}/libgomp*${SOLIBS}"
SUMMARY_libgomp = "GNU OpenMP parallel programming library"
FILES_libgomp-dev = "\
    ${libdir}/libgomp*${SOLIBSDEV} \
    ${libdir}/libgomp*.la \
    ${libdir}/libgomp.spec \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/include/omp.h \
    ${libdir}/gcc/${TARGET_SYS}/${BINV}/include/openacc.h \
"
SUMMARY_libgomp-dev = "GNU OpenMP parallel programming library - development files"
FILES_libgomp-staticdev = "${libdir}/libgomp*.a"
SUMMARY_libgomp-staticdev = "GNU OpenMP parallel programming library - static development files"

FILES_libatomic = "${libdir}/libatomic.so.*"
SUMMARY_libatomic = "GNU C++11 atomics support library"
FILES_libatomic-dev = "\
    ${libdir}/libatomic.so \
    ${libdir}/libatomic.la \
"
SUMMARY_libatomic-dev = "GNU C++11 atomics support library - development files"
FILES_libatomic-staticdev = "${libdir}/libatomic.a"
SUMMARY_libatomic-staticdev = "GNU C++11 atomics support library - static development files"

FILES_libitm = "${libdir}/libitm.so.*"
SUMMARY_libitm = "GNU transactional memory support library"
FILES_libitm-dev = "\
    ${libdir}/libitm.so \
    ${libdir}/libitm.la \
    ${libdir}/libitm.spec \
"
SUMMARY_libitm-dev = "GNU transactional memory support library - development files"
FILES_libitm-staticdev = "${libdir}/libitm.a"
SUMMARY_libitm-staticdev = "GNU transactional memory support library - static development files"

EAT_VER_MAIN ??= ""

python () {
    if not d.getVar("EAT_VER_MAIN", False):
        raise bb.parse.SkipPackage("External ARM toolchain not configured (EAT_VER_MAIN not set).")
    if d.getVar('TCLIBC', True) != "glibc":
        raise bb.parse.SkipPackage("incompatible with %s" % d.getVar('TCLIBC', True))
}
