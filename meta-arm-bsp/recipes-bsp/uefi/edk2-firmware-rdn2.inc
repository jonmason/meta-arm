# RD N2 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "RdN2"
EDK2_PLATFORM_DSC  = "Platform/ARM/SgiPkg/RdN2/RdN2.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"

COMPATIBLE_MACHINE = "rdn2"

SRCREV_edk2           = "4af58495561278551e1d4dd5a32be1c17b788b00"
SRCREV_edk2-platforms = "8383fb3d45b8afa1e28295b35cf69a50f12fd725"

WARN_QA:remove = "patch-status"
ERROR_QA:remove = "patch-status"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += "\
    file://0001-MdePkg-Cper.h-Add-macros-for-ARM-Processor-Error-Sec.patch \
    file://0002-MdeModulePkg-Allow-dynamic-generation-of-HEST-ACPI-t.patch \
    file://0003-ArmPlatformPkg-add-MM_HEST_ERROR_SOURCE_DESC_PROTOCO.patch \
    file://0004-ArmPlatformPkg-retreive-error-source-descriptors-fro.patch \
    file://0005-MdePkg-add-macro-to-MmCommunication-protocol.patch \
    file://0006-EmbeddedPkg-Add-helpers-for-HEST-table-generation.patch \
    file://0007-ArmPlatformPkg-HEST-ArmPlatformPkg-Add-Readme-file.patch \
    file://0008-StandaloneMmPkg-Drivers-StandaloneMmCpu-Avoid-redund.patch \
    file://0009-MdePkg-IndustryStandard-add-missing-header-to-Arm-Er.patch \
    file://0010-DynamicTablesPkg-add-update-resource-updater-APIs.patch \
    file://0011-MdePkg-Add-CEDT-structure.patch \
    file://0012-ArmPkg-Change-PcdFfaEnable-flag-datatype.patch \
    file://0013-StandaloneMmPkg-Allocate-and-initialise-SP-stack-fro.patch \
    file://0014-StandaloneMmPkg-Include-libfdt-in-the-StMM.patch \
    file://0015-ArmPkg-Add-data-structures-to-receive-FF-A-boot-info.patch \
    file://0016-ArmPkg-ArmFfaSvc-Add-helper-macros-and-fids.patch \
    file://0017-ArmPkg-Add-support-for-FFA_MEM_PERM_GET-SET-ABIs.patch \
    file://0018-StandaloneMmPkg-define-new-data-structure-to-stage-F.patch \
    file://0019-StandaloneMmPkg-Add-support-to-detect-FF-A-v1.1-in-a.patch \
    file://0020-StandaloneMmPkg-parse-SP-manifest-and-populate-new-b.patch \
    file://0021-StandaloneMmPkg-Populate-Hoblist-for-SP-init-from-St.patch \
    file://0022-StandaloneMmPkg-Skip-zero-sized-sections-while-tweak.patch \
    file://0023-StandaloneMmPkg-Add-global-check-for-FF-A-abis.patch \
    file://0024-ArmPkg-Bump-the-StMM-SP-FF-A-minor-version-to-1.patch \
    file://0025-ArmPkg-MmCommunicationDxe-Introduce-FF-A-version-che.patch \
    file://0026-ArmPkg-MmCommunicationDxe-Add-support-for-obtaining-.patch \
    file://0027-ArmPkg-MmCommunicationDxe-Register-FF-A-RX-TX-buffer.patch \
    file://0028-ArmPkg-MmCommunicationDxe-Unmap-FF-A-RX-TX-buffers-d.patch \
    file://0029-ArmPkg-MmCommunicationDxe-Discover-the-StMM-SP.patch \
    file://0030-ArmPkg-MmCommunicationDxe-use-the-FF-A-transport-for.patch \
    file://0031-StandaloneMmPkg-Fix-support-for-receiving-MM-request.patch \
    file://0032-ArmPkg-Enable-FF-A-in-DXE-MM-communication-driver.patch \
    file://0033-StandaloneMmPkg-Add-support-to-handle-FFA-interrupt-.patch \
    file://0034-Fix-FF-A-prototype-to-run-StMM-on-top-of-Hafnium.patch \
    file://0035-Introduce-ArmPlatformPkg-ArmFfaConsoleLib.patch \
    file://0036-FFA-Use-the-offset-field-to-calculate-the-sp-membase.patch \
    file://0037-MdePkg-Acpi64-adds-EINJ-specific-structures.patch \
    file://0038-Revert-BaseTools-Move-GnuNoteBti.bin-to-BaseTools.patch \
    file://0039-Revert-BaseTools-Move-GccLto-Files-to-BaseTools.patch \
    file://0040-MdePkg-Add-AEST-table-specific-definitions.patch \
    file://0041-MdePkg-Update-SIGNATE_64-definition.patch \
    file://0042-CreateHobList-Do-not-add-MMRAM-carveout-in-resource-.patch \
    file://0043-HACK-StandaloneMmPkg-Core-Skip-creation-of-shadow-BF.patch \
"
SRC_URI += "\
    file://0001-Platform-Sgi-add-no-stack-protector-flag-for-StMM-bu.patch;patchdir=edk2-platforms \
    file://0002-Platform-Sgi-Add-support-to-disable-isolated-cpus.patch;patchdir=edk2-platforms \
    file://0003-Platform-Sgi-Define-SLC-supported-PPTT-container.patch;patchdir=edk2-platforms \
    file://0004-Platform-Sgi-Fix-cache-ID-macro-s-comments-and-param.patch;patchdir=edk2-platforms \
    file://0005-Platform-Sgi-Migrate-to-PPTT-with-SLC-for-RD-N2-Cfg1.patch;patchdir=edk2-platforms \
    file://0006-Platform-Sgi-parameterize-the-iort-table.patch;patchdir=edk2-platforms \
    file://0007-Platform-Sgi-generate-pcie-rootbridge-topology-layou.patch;patchdir=edk2-platforms \
    file://0008-Platform-Sgi-Enable-auto-generation-of-PCIE-Table.patch;patchdir=edk2-platforms \
    file://0009-Platform-Sgi-enable-autogeneration-of-iort-table.patch;patchdir=edk2-platforms \
    file://0010-Platform-Sgi-Enable-auto-generation-and-installation.patch;patchdir=edk2-platforms \
    file://0011-Platform-Sgi-Update-ITS-block-entries-in-Madt-table-.patch;patchdir=edk2-platforms \
    file://0012-Platform-Sgi-add-helper-macros-for-DMA-Named-Compone.patch;patchdir=edk2-platforms \
    file://0013-Platform-Sgi-enable-firmware-first-error-handling.patch;patchdir=edk2-platforms \
    file://0014-Platform-Sgi-Define-values-for-ACPI-table-header.patch;patchdir=edk2-platforms \
    file://0015-Platform-Sgi-Add-platform-error-handling-driver.patch;patchdir=edk2-platforms \
    file://0016-Platform-ARM-Add-CPU-RAS-error-handling-driver.patch;patchdir=edk2-platforms \
    file://0017-Platform-Sgi-Enable-EINJ-ACPI-table.patch;patchdir=edk2-platforms \
    file://0018-Platform-Sgi-Add-memory-map-entry-for-EINJ-buffer.patch;patchdir=edk2-platforms \
    file://0019-Platform-Sgi-Add-EINJ-trigger-error-action-table.patch;patchdir=edk2-platforms \
    file://0020-Platform-ARM-Add-Base-Element-RAM-ECC-error-handling.patch;patchdir=edk2-platforms \
    file://0021-Platform-Sgi-ACPI-AEST-table-for-RD-N2-Cfg1-platform.patch;patchdir=edk2-platforms \
    file://0022-Platform-Sgi-Add-Kernel-first-support-on-RD-N2-Cfg1-.patch;patchdir=edk2-platforms \
    file://0023-Platform-Sgi-Add-memory-map-entry-for-debug-uart-con.patch;patchdir=edk2-platforms \
    file://0024-Platform-Sgi-Add-fdtlib-and-PcdFfaEnable.patch;patchdir=edk2-platforms \
    file://0025-StandaloneMm-Enable-libftd-support.patch;patchdir=edk2-platforms \
    file://0026-Platform-Sgi-enable-dynamic-acpi-table-generation-fo.patch;patchdir=edk2-platforms \
    file://0027-Platform-Sgi-enable-support-for-dram-size-configurat.patch;patchdir=edk2-platforms \
    file://0028-Platform-Sgi-Update-fastchannel-address-for-RD-N2-va.patch;patchdir=edk2-platforms \
    file://0029-Platform-Sgi-add-helper-macros-for-acpi-table-genera.patch;patchdir=edk2-platforms \
    file://0030-Platform-Sgi-Add-initial-support-for-RD-V3-Cfg1-plat.patch;patchdir=edk2-platforms \
    file://0031-Platform-ARM-SgiPkg-Add-initial-support-for-RD-V3-Cf.patch;patchdir=edk2-platforms \
    file://0032-Platform-SgiPkg-enable-StMM-build-for-RdV3.patch;patchdir=edk2-platforms \
    file://0033-SgiPkg-Update-StandaloneMM-load-address.patch;patchdir=edk2-platforms \
    file://0034-Platform-Sgi-Add-MPAM-ACPI-macros-in-common-header.patch;patchdir=edk2-platforms \
    file://0035-Platform-Sgi-Add-MPAM-ACPI-table-for-RD-N2-Cfg1.patch;patchdir=edk2-platforms \
    file://0036-Sgi-Move-StMM-communication-carveout-out-of-secure-r.patch;patchdir=edk2-platforms \
    file://0037-TEMP-add-iovirtblk-count-pcd-to-rdn2cfg2-acpi.patch;patchdir=edk2-platforms \
    file://0038-TEMP-RdN2-AcpiTables-remove-SsdtIoVirtSocEx-table.patch;patchdir=edk2-platforms \
    file://0039-Platform-Sgi-Enable-PCIe-support-on-RdV3.patch;patchdir=edk2-platforms \
    file://0040-Platform-Sgi-Enable-PCIe-support-on-RdN2.patch;patchdir=edk2-platforms \
    file://0041-Platform-Sgi-Allow-non-secure-transactions-with-SMMU.patch;patchdir=edk2-platforms \
    file://0042-Platform-Sgi-add-remote-memory-descriptor.patch;patchdir=edk2-platforms \
    file://0043-Platform-Sgi-prepare-SRAT-HMAT-table.patch;patchdir=edk2-platforms \
    file://0044-Platform-Sgi-Add-CXL-Early-Discovery-Table-CEDT-for-.patch;patchdir=edk2-platforms \
    file://0045-Platform-ARM-add-CXL-driver.patch;patchdir=edk2-platforms \
    file://0046-Platform-Sgi-add-CXL-driver-support.patch;patchdir=edk2-platforms \
    file://0047-Platform-Sgi-add-CXL-specific-ACPI-tables.patch;patchdir=edk2-platforms \
    file://0048-Platform-ARM-Enable-EINJ-ACPI-table-for-Rd-V3-Cfg1.patch;patchdir=edk2-platforms \
    file://0049-Platform-ARM-Enable-AEST-ACPI-table-for-Rd-V3-Cfg1.patch;patchdir=edk2-platforms \
    file://0050-Platform-ARM-update-the-fdf-and-inf-files.patch;patchdir=edk2-platforms \
    file://0051-Platform-ARM-Make-RAS-PCD-s-plaform-specific.patch;patchdir=edk2-platforms \
    file://0052-Platform-ARM-Refactor-RdN2Cfg1-EINJ-PCD-to-Plaform-s.patch;patchdir=edk2-platforms \
    file://0053-Platform-ARM-Refactor-RdV3Cfg1-EINJ-PCD-to-Plaform-s.patch;patchdir=edk2-platforms \
    file://0054-Platform-ARM-Update-SRAM-driver.patch;patchdir=edk2-platforms \
    file://0055-Platform-ARM-Remove-MCfg.aslc-and-SsdIoVirtSocExp.as.patch;patchdir=edk2-platforms \
    file://0056-Platform-sgi-add-vendor-error-extenstion-structure-f.patch;patchdir=edk2-platforms \
    file://0057-Platform-sgi-update-SetErrorTypeAddress-in-RdN2Cfg1-.patch;patchdir=edk2-platforms \
    file://0058-Platform-Sgi-Add-MPAM-ACPI-table-for-RD-V3-Cfg1.patch;patchdir=edk2-platforms \
    file://0059-Platform-Sgi-Include-HobPrintLib.patch;patchdir=edk2-platforms \
    file://0060-Platform-ARM-Switch-to-new-Stack-Check-lib.patch;patchdir=edk2-platforms \
    file://0061-Platform-Sgi-Rename-FREMONT-to-RDV3-in-SgiPlatform-M.patch;patchdir=edk2-platforms \
    file://0062-Platform-Sgi-Add-Memorymap-file-for-RDV3-R1-platform.patch;patchdir=edk2-platforms \
    file://0063-Platform-Sgi-Create-voyager-r1-platform-specific-dsc.patch;patchdir=edk2-platforms \
    file://0064-Platform-Sgi-Add-initial-support-for-RDV3R1-Platform.patch;patchdir=edk2-platforms \
    file://0065-Platform-Sgi-Add-ACPI-tables-for-RDV3R1-platform.patch;patchdir=edk2-platforms \
    file://0066-Platform-Sgi-Add-initial-support-for-RDV3R1CFG1-plat.patch;patchdir=edk2-platforms \
    file://0067-Platform-Sgi-Add-ACPI-tables-for-RDV3R1CFG1-platform.patch;patchdir=edk2-platforms \
    file://0068-Platform-SgiPkg-Enable-StMM-build-for-RdV3R1.patch;patchdir=edk2-platforms \
    file://0069-Platform-Sgi-define-PCD-for-generic-timer-base-addre.patch;patchdir=edk2-platforms \
    file://0070-Revert-Platform-Sgi-Update-fastchannel-address-for-R.patch;patchdir=edk2-platforms \
    file://0071-Platform-Sgi-Enable-PCIe-support-on-RdV3.patch;patchdir=edk2-platforms \
    file://0072-Platform-Sgi-Enable-PCIe-support-on-RdN2.patch;patchdir=edk2-platforms \
    file://0073-Platform-ARM-Add-CMN-device-nodes-to-AEST-table.patch;patchdir=edk2-platforms \
    file://0074-Platform-ARM-Add-DSDT-entry-for-CMN-800.patch;patchdir=edk2-platforms \
    file://0075-Platform-Sgi-Fix-incorrect-Config-ID-for-RD-V3.patch;patchdir=edk2-platforms \
    file://0076-Platform-Sgi-Update-DRAM-Block2-Base-Address-PCD.patch;patchdir=edk2-platforms \
    file://0077-Platform-Sgi-Add-Firmware-Version-Support.patch;patchdir=edk2-platforms \
    file://0078-Platform-Sgi-autogenerate-SoC-expansion-block-iort-t.patch;patchdir=edk2-platforms \
"
