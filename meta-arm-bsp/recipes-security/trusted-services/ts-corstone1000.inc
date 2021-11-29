FILESEXTRAPATHS:prepend := "${THISDIR}/secure-partitions:"

COMPATIBLE_MACHINE = "corstone1000"

SRC_URI:append = " file://0001-tools-cmake-common-applying-lowercase-project-convention.patch \
                  file://0002-fix-EARLY_TA_PATHS-env-variable.patch \
                  file://0003-se-proxy-dts-add-se-proxy-as-child-node.patch \
		  "

TS_PLATFORM = "arm/fvp/fvp_base_revc-2xaemv8a"
TS_ENVIRONMENT = "opteesp"
SP_PACKAGING_METHOD = "embedded"

EXTRA_OEMAKE += "TS_PLATFORM=${TS_PLATFORM}"

# Secure Enclave proxy secure partition
TS_DEPLOYMENTS += "'deployments/se-proxy/${TS_ENVIRONMENT}'"
