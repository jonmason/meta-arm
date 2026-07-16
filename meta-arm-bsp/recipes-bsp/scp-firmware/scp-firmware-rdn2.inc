# RD N2 specific SCP configurations and build instructions

COMPATIBLE_MACHINE:rdn2 = "rdn2"
SCP_PRODUCT_GROUP = "neoverse-rd"
SCP_PLATFORM = "rdn2"

EXTRA_OECMAKE += "-D SCP_PLATFORM_VARIANT=0"

SCP_LOG_LEVEL = "DEBUG"

#SRC_URI_SCP_FIRMWARE = "gitsm://gitlab.arm.com/infra-solutions/reference-design/platsw/scp-firmware.git;protocol=https"
#SRCBRANCH = "refinfra-bmc"
SRCREV  = "f76402dfefc7557b97aac6226c0b1302e2dc5e12"
SRC_URI:remove = "file://0001-OPTEE-Private-Includes.patch"

INSANE_SKIP:${PN} += "buildpaths"
INSANE_SKIP:${PN}-dbg += "buildpaths"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"
SRC_URI += "\
    file://0001-TEMP-module-cmn_cyprus-extend-support-for-32-HTG-reg.patch \
    file://0002-TEMP-cmn700-program-hnf-sam-end-addr-before-start-ad.patch \
    file://0003-neoverse-rd-module-add-io-block-driver.patch \
    file://0004-neoverse-rd-rdv3-enable-io-block-driver.patch \
    file://0005-neoverse-rd-pcie_integ_ctrl-define-apis-with-io_bloc.patch \
    file://0006-pcie_discovery-Add-support-to-do-device-discovery.patch \
    file://0007-neoverse-rd-pcie_setup-enable-io-virtualisation-bloc.patch \
    file://0008-neoverse-rd-rdv3-add-support-to-pass-pcie-configurat.patch \
    file://0009-neoverse-rd-pcie_setup-add-additional-params-in-conf.patch \
    file://0010-neoverse-rd-pcie_setup-notification-for-pcie-initial.patch \
    file://0011-neoverse-rd-rdv3-add-pcie_setup-config-file.patch \
    file://0012-neoverse-rd-rdn2-add-pcie-mmap-sds-region.patch \
    file://0013-neoverse-rd-rdn2-enable-dynamic-pcie-setup.patch \
    file://0014-module-cxl-add-support-for-CXL.patch \
    file://0015-module-cmn700-configuring-CCG-for-mapping-Host-addre.patch \
    file://0016-pcie_enumeration-add-api-for-detecting-cxl-device.patch \
    file://0017-Temp-pcie_enumeration-Enable-CXL-support-only-in-RD-.patch \
    file://0018-neoverse-rd-rdv3-add-support-for-SMCF-configuration.patch \
    file://0019-neoverse-rd-rdv3-smcf-Add-Stop-Sampling-in-smcf-modu.patch \
    file://0020-neoverse-rd-rdv3-config_amu_smcf_drv-Add-config-for-.patch \
    file://0021-neoverse-rd-rdv3-smcf-Add-platform-smcf-module-for-R.patch \
    file://0022-neoverse-rd-rdv3-smcf-Add-smcf_client-module-to-read.patch \
    file://0023-neoverse-rd-rdv3-smcf_client-add-smcf-sampling-contr.patch \
    file://0024-module-amu_smcf_drv-add-support-for-configuring-amu_.patch \
    file://0025-neoverse-rd-rdv3-smcf_client-Add-support-for-configu.patch \
    file://0026-neoverse-rd-rdv3-add-crosschip-pcie-mappings.patch \
    file://0027-neoverse-rd-rdv3-enable-Cli-debugger-for-rdv3cfg1.patch \
    file://0028-neoverse-rd-rdv3-Adds-command-line-utility-to-excerc.patch \
    file://0029-neoverse-rd-rdv3-Adds-ras-handler-for-handling-scp-r.patch \
    file://0030-neoverse-rd-rev3-static-atu-mapping-for-scp-einj-uti.patch \
    file://0031-config_atu-Update-the-physical-address-of-Secure-SRA.patch \
    file://0032-neoverse-rd-rdv3-add-timer-module-id-in-the-mhu3-con.patch \
    file://0033-HACK-neoverse-rdv3-disable-the-setting-monitor-mode-.patch \
    file://0034-module-cmn_cyprus-limit-rnf-count-for-dual-chip-syst.patch \
    file://0035-neoverse-rd-rdv3-enable-warm-reboot-support.patch \
    file://0036-rdv3-program-the-AP-RVBAR-for-RESET_TO_BL31.patch \
    file://0037-neoverse-rd-rdv3-clear-LCP-reset-syndrome-register.patch \
    file://0038-neoverse-rd-rdv3r1-add-io-block-driver.patch \
    file://0039-neoverse-rd-rdv3r1-enable-io-block-driver.patch \
    file://0040-neoverse-rd-rdv3r1-add-pcie_setup-config-file.patch \
    file://0041-neoverse-rd-rdv3r1-add-crosschip-pcie-mappings.patch \
    file://0042-tools-rdv3r1-Add-product-variants.patch \
    file://0043-module-cmn_cyprus-Add-compact-HN-table-support.patch \
    file://0044-neoverse-rd-rdv3r1-update-dram-block2-base-address.patch \
    file://0045-neoverse-rd-rdv3r1cfg1-add-platform-Support.patch \
    file://0046-rdv3r1-add-lcp-sram-region-breakout.patch \
    file://0047-rdv3r1-update-lcp-ram-size.patch \
    file://0048-neoverse-rd-rdv3-add-memory-region-that-targets-GIC-.patch \
    file://0049-neoverse-rd-rdv3r1cfg1-fix-ap-boot-flash-hni-target-.patch \
    file://0050-neoverse-rd-rdv3-add-system-pik-module.patch \
    file://0051-neoverse-rd-rdv3-adapt-to-refactoring-of-fwk_module_.patch \
    "
