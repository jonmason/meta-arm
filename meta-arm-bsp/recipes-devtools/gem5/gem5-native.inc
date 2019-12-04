# gem5 platform independent build information

SUMMARY = "A modular platform for computer-system architecture research"
HOMEPAGE = "http://gem5.org"
LICENSE = "BSD & MIT & LGPLv2.1"

# Gem5 build and run parameter

# What gem5 binary are we building
GEM5_BUILD_CONFIGS ?= "build/X86/gem5.opt"

# Scons build arguments
GEM5_SCONS_ARGS ?= "-j ${BB_NUMBER_THREADS} CC=${BUILD_CC} CXX=${BUILD_CXX} \
    AS=${BUILD_AS} AR=${BUILD_AR} ${GEM5_BUILD_CONFIGS}"

# Default profile to run
GEM5_RUN_PROFILE ?= "configs/example/fs.py"

# We are building a native package and we need to use python
inherit native pythonnative

# the build is using several tools:
# python: scons and six
# google protobuf
# pkgconfig
# hdf5
DEPENDS_append = " python-native python-scons-native python-six-native \
                   protobuf-native hdf5-native pkgconfig-native boost-native \
                   libpng-native"

do_configure[noexec] = "1"

do_compile() {
    # We need to use the proper native libraries when executing
    # compiled applications
    export LD_LIBRARY_PATH="${STAGING_LIBDIR_NATIVE}"

    scons ${GEM5_SCONS_ARGS}
}

do_install() {

    install -d ${D}${datadir}/gem5
    cp -a --no-preserve=ownership -rf configs ${D}${datadir}/gem5/.

    for f in ${GEM5_BUILD_CONFIGS}; do
        destname=$(basename $f)
        install -d ${D}${bindir}
        install -m 755 $f ${D}${bindir}/$destname.real
        cat <<EOF > ${D}${bindir}/$destname
#!/bin/bash
basedir=\$(cd \$(dirname \$0)/../../; pwd)
export LD_LIBRARY_PATH="\$basedir/lib:\$basedir/usr/lib"
\$basedir/usr/bin/$destname.real "\$@"
EOF
        chmod a+x ${D}${bindir}/$destname
    done
}

FILES_${PN} = "${datadir}/gem5/* ${bindir}/*"
INSANE_SKIP_${PN} += "already-stripped"
RDEPENDS_${PN} += "python-native hdf5-native protobuf-native libpng-native"

