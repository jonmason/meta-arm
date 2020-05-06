# gcc-target.inc in OE-Core has these 2 lines in do_install():
#
# | # Add unwind.h, it comes from libgcc which we don't want to build again
# | install ${STAGING_LIBDIR_NATIVE}/${TARGET_SYS}/gcc/${TARGET_SYS}/${BINV}/include/unwind.h ${D}${libdir}/gcc/${TARGET_SYS}/${BINV}/include/
#
# When TCMODE="external-arm" libgcc is provided by external-arm-toolchain.bb
# And while it stages the necessary unwind.h file, it ends up in slightly
# different location. While this is a kludge, be very conservative - only
# copy the file for target build in recipe-specific sysroot, in external-arm
# toolchain mode and if the required file does not exist already.

do_install_prepend_class-target () {
	if [ "${TCMODE}" = "external-arm" -a ! -f ${STAGING_LIBDIR_NATIVE}/${TARGET_SYS}/gcc/${TARGET_SYS}/${BINV}/include/unwind.h ]; then
		install -d ${STAGING_LIBDIR_NATIVE}/${TARGET_SYS}/gcc/${TARGET_SYS}/${BINV}/include/
		install ${STAGING_LIBDIR}/gcc/${EAT_TARGET_SYS}/${EAT_VER_GCC}/include/unwind.h ${STAGING_LIBDIR_NATIVE}/${TARGET_SYS}/gcc/${TARGET_SYS}/${BINV}/include/
	fi
}
