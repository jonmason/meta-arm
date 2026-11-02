# RD N2 specific SCP configurations and build instructions

COMPATIBLE_MACHINE:rdn2 = "rdn2"
SCP_PRODUCT_GROUP = "neoverse-rd"
SCP_PLATFORM = "rdn2"

EXTRA_OECMAKE += "-D SCP_PLATFORM_VARIANT=0"

SCP_LOG_LEVEL = "DEBUG"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/rdn2:"

SRC_URI += " \
    file://0001-neoverse-rd-module-add-io-block-driver.patch \
    file://0002-neoverse-rd-pcie_integ_ctrl-define-apis-with-io_bloc.patch \
    file://0003-pcie_discovery-Add-support-to-do-device-discovery.patch \
    file://0004-neoverse-rd-pcie_setup-enable-io-virtualisation-bloc.patch \
    file://0005-neoverse-rd-rdv3-add-support-to-pass-pcie-configurat.patch \
    file://0006-neoverse-rd-pcie_setup-add-additional-params-in-conf.patch \
    file://0007-neoverse-rd-pcie_setup-notification-for-pcie-initial.patch \
    file://0008-neoverse-rd-rdn2-add-pcie-mmap-sds-region.patch \
    file://0009-neoverse-rd-rdn2-enable-dynamic-pcie-setup.patch \
    file://0010-module-cxl-add-support-for-CXL.patch \
    file://0011-module-cmn700-configuring-CCG-for-mapping-Host-addre.patch \
    file://0012-pcie_enumeration-add-api-for-detecting-cxl-device.patch \
    file://0013-Temp-pcie_enumeration-Enable-CXL-support-only-in-RD-.patch \
    file://0014-TEMP-cmn700-program-hnf-sam-end-addr-before-start-ad.patch \
"
