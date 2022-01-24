SUMMARY = "PSA arch test application"

require secure-partitions.inc

LIC_FILES_CHKSUM += "file://../psa-arch-tests/LICENSE.md;md5=2a944942e1496af1886903d274dedb13"
SRC_URI_PSA = "git://github.com/ARM-software/psa-arch-tests.git;protocol=https;branch=main;name=psa;destsuffix=git/psa-arch-tests"
SRC_URI:append = " ${SRC_URI_PSA}"

SRCREV_FORMAT="ts_psa"
SRCREV_psa = "6e1549dde62d12c92fc2df90ebbbe2d2d77cc76a"
PV = "1.2+git${SRCPV}"

PSA_APPLICATION_NAME = "psa-api-test"
TS_ENVIRONMENT_LINUX = "arm-linux"

PSA_API_TESTS += "deployments/psa-api-test/protected_storage/${TS_ENVIRONMENT_LINUX}"
PSA_API_TESTS += "deployments/psa-api-test/internal_trusted_storage/${TS_ENVIRONMENT_LINUX}"
PSA_API_TESTS += "deployments/psa-api-test/initial_attestation/${TS_ENVIRONMENT_LINUX}"
PSA_API_TESTS += "deployments/psa-api-test/crypto/${TS_ENVIRONMENT_LINUX}"

EXTRA_OECMAKE += "-DCMAKE_POSITION_INDEPENDENT_CODE=True \
                 -DCMAKE_SYSTEM_NAME=Linux \
                 -DCMAKE_SYSTEM_PROCESSOR=arm \
                "

do_deploy[noexec] = "1"
