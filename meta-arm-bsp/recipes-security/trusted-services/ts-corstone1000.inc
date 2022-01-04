FILESEXTRAPATHS:prepend := "${THISDIR}/secure-partitions:"

COMPATIBLE_MACHINE = "corstone1000"

LIC_FILES_CHKSUM += "file://../mbedcrypto/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
                                             file://../nanopb/LICENSE.txt;md5=9db4b73a55a3994384112efcdb37c01f \
                                             file://../openamp/LICENSE.md;md5=a8d8cf662ef6bf9936a1e1413585ecbf \
					     file://../libmetal/LICENSE.md;md5=fe0b8a4beea8f0813b606d15a3df3d3c \
                                             "


SRC_URI:append = " \
                 ${SRC_URI_MBED} ${SRC_URI_NANOPB} ${SRC_URI_OPENAMP} ${SRC_URI_LIBMETAL} \
                  file://0001-tools-cmake-common-applying-lowercase-project-convention.patch \
                  file://0002-fix-EARLY_TA_PATHS-env-variable.patch \
                  file://0003-se-proxy-dts-add-se-proxy-as-child-node.patch \
                  file://0004-Update-mm-comm-buffer-region-in-dts-file.patch \
                  file://0005-Configure-NV-storage-macro.patch \
                  file://0006-Use-device-region.patch \
                  file://0007-Add-openamp-to-SE-proxy-deployment.patch \
                  file://0008-Implement-mhu-driver-and-the-OpenAmp-conversion-laye.patch \
                  file://0009-Add-openamp-rpc-caller.patch \
                  file://0010-add-psa-client-definitions-for-ff-m.patch \
                  file://0011-Add-common-service-component-to-ipc-support.patch \
                  file://0012-Add-secure-storage-ipc-backend.patch \
                  file://0013-Use-secure-storage-ipc-and-openamp-for-se_proxy.patch \
                  file://0014-Add-uefi-variable-append-write-support.patch \
                  file://0015-Add-UEFI-variable-support-for-QueryVariableInfo.patch \
                  file://0016-Add-uefi-test-deployment.patch \
                  file://0017-Fix-interface-ID-parameter-setting-in-sp-ffarpc_call.patch \
                  file://0018-Support-FFARPC-call-requests-with-no-shared-buffer.patch \
                  file://0019-Run-psa-arch-test.patch \
                  file://0020-Use-address-instead-of-pointers.patch \
                  file://0021-Add-psa-ipc-attestation-to-se-proxy.patch \
                  file://0022-Setup-its-backend-as-openamp-rpc-using-secure-storag.patch \
                  file://0023-add-psa-ipc-crypto-backend.patch \
                  file://0024-Increase-SMM-gateway-UEFI-variable-macro-value.patch \
                  file://0025-Add-stub-capsule-update-service-components.patch \
                  file://0026-Add-logs-to-functions-in-SMM-gateway-SP.patch \
                  file://0027-Configure-storage-size.patch \
                  file://0028-Revert-Add-uefi-variable-append-write-support.patch \
                  file://0029-Change-UID-of-variable-index-in-SMM.patch \
                  file://0030-Add-missing-features-to-setVariable.patch \
                  file://0031-Add-invalid-parameter-check-in-getNextVariableName.patch \
                  file://0032-smm_gateway-add-checks-for-null-attributes.patch \
                  "

SRC_URI_MBED = "git://github.com/ARMmbed/mbed-crypto.git;protocol=https;branch=development;name=mbed;destsuffix=git/mbedcrypto"
SRCREV_mbed = "cf4a40ba0a3086cabb5a8227245191161fd26383"

SRC_URI_NANOPB = "git://github.com/nanopb/nanopb.git;name=nanopb;protocol=https;branch=master;destsuffix=git/nanopb"
SRCREV_nanopb = "df0e92f474f9cca704fe2b31483f0b4d1b1715a4"

SRC_URI_OPENAMP = "git://github.com/OpenAMP/open-amp.git;name=openamp;protocol=https;branch=main;destsuffix=git/openamp"
SRCREV_openamp = "347397decaa43372fc4d00f965640ebde042966d"

SRC_URI_LIBMETAL = "git://github.com/OpenAMP/libmetal.git;name=libmetal;protocol=https;branch=main;destsuffix=git/libmetal"
SRCREV_libmetal = "f252f0e007fbfb8b3a52b1d5901250ddac96baad"

TS_PLATFORM = "arm/corstone1000"
TS_ENVIRONMENT = "opteesp"
SP_PACKAGING_METHOD = "embedded"

# Secure Enclave proxy secure partition
TS_DEPLOYMENTS += "'deployments/se-proxy/${TS_ENVIRONMENT}'"

# smm-gateway secure partition
TS_DEPLOYMENTS += "'deployments/smm-gateway/${TS_ENVIRONMENT}'"
