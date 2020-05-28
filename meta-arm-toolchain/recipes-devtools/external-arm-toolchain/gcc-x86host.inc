COMPATIBLE_HOST = "x86_64.*-linux"

FILES_${PN} = "${datadir} ${bindir}"

BINNAME = "${@d.getVar("BPN").strip("gcc-")}"

do_install() {
    install -d ${D}${datadir}/${BINNAME}/
    cp -r ${S}/. ${D}${datadir}/

    install -d ${D}${bindir}
    # Symlink all executables into bindir
    for f in ${D}${datadir}/${BINNAME}/bin/${BINNAME}-*; do
        lnr $f ${D}${bindir}/$(basename $f)
    done
}

INSANE_SKIP_${PN} = "already-stripped libdir staticdev file-rdeps"

INHIBIT_SYSROOT_STRIP = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

BBCLASSEXTEND = "native nativesdk"
