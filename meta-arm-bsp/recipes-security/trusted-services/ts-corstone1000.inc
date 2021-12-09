FILESEXTRAPATHS:prepend := "${THISDIR}/secure-partitions:"

COMPATIBLE_MACHINE = "corstone1000"

LIC_FILES_CHKSUM += "file://../mbedcrypto/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
                                             file://../nanopb/LICENSE.txt;md5=9db4b73a55a3994384112efcdb37c01f"


SRC_URI:append = " \
                 ${SRC_URI_MBED} ${SRC_URI_NANOPB} \
                  file://0001-tools-cmake-common-applying-lowercase-project-convention.patch \
                  file://0002-fix-EARLY_TA_PATHS-env-variable.patch \
                  file://0003-se-proxy-dts-add-se-proxy-as-child-node.patch \
                  file://0004-Update-mm-comm-buffer-region-in-dts-file.patch \
                  file://0005-Configure-NV-storage-macro.patch \
                  file://0006-Use-device-region.patch \
		  "

SRCREV_ts = "882a2db4f9181fc6ddb505b82262f82e5a0c2fd5"

SRC_URI_MBED = "git://github.com/ARMmbed/mbed-crypto.git;protocol=https;branch=development;name=mbed;destsuffix=git/mbedcrypto"
SRCREV_mbed = "cf4a40ba0a3086cabb5a8227245191161fd26383"

SRC_URI_NANOPB = "git://github.com/nanopb/nanopb.git;name=nanopb;protocol=https;branch=master;destsuffix=git/nanopb"
SRCREV_nanopb = "df0e92f474f9cca704fe2b31483f0b4d1b1715a4"

TS_PLATFORM = "arm/fvp/fvp_base_revc-2xaemv8a"
TS_ENVIRONMENT = "opteesp"
SP_PACKAGING_METHOD = "embedded"

EXTRA_OEMAKE += "TS_PLATFORM=${TS_PLATFORM}"

# Secure Enclave proxy secure partition
TS_DEPLOYMENTS += "'deployments/se-proxy/${TS_ENVIRONMENT}'"

# smm-gateway secure partition
TS_DEPLOYMENTS += "'deployments/smm-gateway/${TS_ENVIRONMENT}'"
