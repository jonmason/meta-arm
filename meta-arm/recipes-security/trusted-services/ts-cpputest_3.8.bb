SUMMARY = "CppUTest for trusted services"
DESCRIPTION = "CppUTest unit testing and mocking framework for C/C++"
HOMEPAGE = "http://cpputest.github.io/"

LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://COPYING;md5=ce5d5f1fe02bcd1343ced64a06fd4177"

SRC_URI = "git://github.com/cpputest/cpputest.git \
           file://cpputest-cmake-fix.patch \
           "
SRCREV = "e25097614e1c4856036366877a02346c4b36bb5b"

PV = "3.8+git${SRCPV}"

S = "${WORKDIR}/git"

inherit cmake

OECMAKE_GENERATOR = "Unix Makefiles"
EXTRA_OECMAKE = "-DCMAKE_POSITION_INDEPENDENT_CODE=True \
                 -DMEMORY_LEAK_DETECTION=OFF \
                 -DLONGLONG=ON \
                 -DC++11=ON \
                 -DTESTS=OFF \
                 -DEXTENSIONS=OFF \
                 -DHAVE_FORK=OFF \
                 -DCPP_PLATFORM=armcc \
                 -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
                 "
FILES_${PN} += "/usr/lib/CppUTest/* /usr/lib/CppUTest/cmake/*"
