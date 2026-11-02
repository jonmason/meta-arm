# RD N2 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "RdN2"
EDK2_PLATFORM_DSC  = "Platform/ARM/SgiPkg/RdN2/RdN2.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"

COMPATIBLE_MACHINE = "rdn2"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/rdn2:"

SRC_URI:append = " \
    file://0001-DynamicTablesPkg-retain-QWord-translation-for-PCIe-t.patch \
    file://0002-Changes-in-acpica-20260408-are-now-causing-issues-wi.patch;patchdir=edk2-platforms \
    file://0003-Platform-Sgi-generate-pcie-rootbridge-topology-layou.patch;patchdir=edk2-platforms \
    file://0004-Platform-Sgi-Enable-auto-generation-of-PCIE-Table.patch;patchdir=edk2-platforms \
    file://0005-Platform-Sgi-enable-autogeneration-of-iort-table.patch;patchdir=edk2-platforms \
    file://0006-Platform-Sgi-Enable-auto-generation-and-installation.patch;patchdir=edk2-platforms \
    file://0007-Platform-Sgi-Enable-PCIe-support-on-RdN2.patch;patchdir=edk2-platforms \
    file://0008-Platform-Sgi-retain-PCIe-enable-after-RdN2-includes.patch;patchdir=edk2-platforms \
    file://0009-Platform-Sgi-autogenerate-SoC-expansion-block-iort-t.patch;patchdir=edk2-platforms \
    file://0010-Platform-Sgi-define-SMMU-PCDs-for-dynamic-IORT.patch;patchdir=edk2-platforms \
    file://0011-Platform-Sgi-use-FdtLib-and-BaseMemoryLib-for-PCIe-t.patch;patchdir=edk2-platforms \
    file://0012-Platform-Sgi-add-helper-macros-for-DMA-Named-Compone.patch;patchdir=edk2-platforms \
"
