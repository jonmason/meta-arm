require fvp-common.inc

HOMEPAGE = "https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms/arm-ecosystem-models"

do_install() {
    mkdir --parents ${D}${FVPDIR} ${D}${bindir}

    cp --archive --no-preserve=ownership ${S}/*_pkg/* ${D}${FVPDIR}/

    fvp_link_binaries
}
