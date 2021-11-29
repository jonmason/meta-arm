FILESEXTRAPATHS:prepend := "${THISDIR}/secure-partitions:"

COMPATIBLE_MACHINE = "corstone1000"

SRCREV_ts = "882a2db4f9181fc6ddb505b82262f82e5a0c2fd5"
SRC_URI:append = " file://0001-tools-cmake-common-applying-lowercase-project-convention.patch \
                  file://0002-fix-EARLY_TA_PATHS-env-variable.patch \
                  file://0003-se-proxy-dts-add-se-proxy-as-child-node.patch \
                  file://0004-Update-mm-comm-buffer-region-in-dts-file.patch \
                  file://0005-Configure-NV-storage-macro.patch \
                  file://0006-Use-device-region.patch \
		  "

TS_PLATFORM = "arm/fvp/fvp_base_revc-2xaemv8a"
TS_ENVIRONMENT = "opteesp"
SP_PACKAGING_METHOD = "embedded"

EXTRA_OEMAKE += "TS_PLATFORM=${TS_PLATFORM}"

# Secure Enclave proxy secure partition
TS_DEPLOYMENTS += "'deployments/se-proxy/${TS_ENVIRONMENT}'"

# smm-gateway secure partition
TS_DEPLOYMENTS += "'deployments/smm-gateway/${TS_ENVIRONMENT}'"
