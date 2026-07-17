# RD N2 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "RdN2"
EDK2_PLATFORM_DSC  = "Platform/ARM/SgiPkg/RdN2/RdN2.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"

COMPATIBLE_MACHINE = "rdn2"

#SRC_URI_EDK2 = "gitsm://gitlab.arm.com/infra-solutions/reference-design/platsw/edk2.git;protocol=https"
SRC_URI_EDK2_PLATFORMS = "git://gitlab.arm.com/infra-solutions/reference-design/platsw/edk2-platforms.git;protocol=https"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append = " file://0001-Changes-in-acpica-20260408-are-now-causing-issues-wi.patch;patchdir=edk2-platforms"

#SRCBRANCH_edk2 = "refinfra"
SRCBRANCH_edk2_platforms = "refinfra"

# Use the RD-INFRA-2024.12.20 tag
#SRCREV_edk2           = "dd25905d63ec72d6e06804155fda1098d10da19e"
SRCREV_edk2           = "4af58495561278551e1d4dd5a32be1c17b788b00"


SRC_URI:append = " \
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


SRCREV_edk2-platforms = "f6ed3b0f92eeaf380638f77d8b5ace805facb301"
