# tf-a-tests
#

# Never select this if another version is available
DEFAULT_PREFERENCE = "-1"

require tf-a-tests.inc

SRC_URI = "git://git.trustedfirmware.org/TF-A/tf-a-tests.git;;protocol=https;name=tfa-tests"
SRCREV_FORMAT = "tfa-tests"

S = "${WORKDIR}/git"

# The following hack is needed to fit properly in yocto build environment
# TFA is forcing the host compiler and its flags in the Makefile using :=
# assignment for GCC and CFLAGS.
# To properly use the native toolchain of yocto and the right libraries we need
# to pass the proper flags to gcc. This is achieved here by creating a gcc
# script to force passing to gcc the right CFLAGS and LDFLAGS
do_compile_prepend() {
    # Create an host gcc build parser to ensure the proper include path is used
    mkdir -p bin
    echo "#!/usr/bin/env bash" > bin/gcc
    echo "$(which ${BUILD_CC}) ${BUILD_CFLAGS} ${BUILD_LDFLAGS} \$@" >> bin/gcc
    chmod a+x bin/gcc
    export PATH="$PWD/bin:$PATH"
}
