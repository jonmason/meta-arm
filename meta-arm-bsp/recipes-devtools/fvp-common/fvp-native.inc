# Fixed Virtual Platform (FVP) executable installation recipe

#
# Package specific information like checksums and source information captured
# in specific bb files.
#

SUMMARY = "Arm Fixed Virtual Platform"
HOMEPAGE = "https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms"
LICENSE = "Proprietary & GPL & Apache"


inherit native deploy

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    install -d ${D}/${datadir}/fvp
    install -d ${D}${bindir}
}
FILES_${PN} = "${datadir}/fvp/* ${bindir}/*"
INSANE_SKIP_${PN}_append = "already-stripped"

# This is required so that our binaries are in the sysroot. We need this
# to have both fvp required libraries and fvp in the same sysroot.
addtask addto_recipe_sysroot after do_populate_sysroot before do_build

do_deploy[sstate-outputdirs] = "${DEPLOY_DIR_TOOLS}"
do_deploy() {
    install -d ${DEPLOYDIR}
}
addtask deploy before do_build after do_compile

