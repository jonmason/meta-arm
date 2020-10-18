#
# N1SDP MACHINE specific configurations
#

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-5.4:"

# Apply N1SDP specific patches
SRC_URI_append_n1sdp = " \
    file://0001-TMP-iommu-arm-smmu-v3-Ignore-IOPF-capabilities.patch \
    file://0002-pci_quirk-add-acs-override-for-PCI-devices.patch \
    file://0003-pcie-Add-quirk-for-the-Arm-Neoverse-N1SDP-platform.patch \
    file://0004-n1sdp-update-n1sdp-pci-quirk-for-SR-IOV-support.patch \
    file://0005-n1sdp-pcie-add-quirk-support-enabling-remote-chip-PC.patch \
    file://enable-realtek-R8169.cfg \
    file://scripts-dtc-remove-redundant-YYLOC.patch \
    "

# Referring to commit TAG N1SDP-2020.07.27
SRCREV_n1sdp  = "84baaae9e751c058717d9702438429257f077f03"
SRCREV_dts_n1sdp = "3209a868152f348194cc1f20fd87c759d3a97d45"

# Use intree defconfig
KBUILD_DEFCONFIG_n1sdp = "defconfig"

# Since the intree defconfig in n1sdp kernel repository is not setting all the configs,
# KCONFIG_MODE is set to "alldefconfig" to properly expand the defconfig.
KCONFIG_MODE_n1sdp = "--alldefconfig"

COMPATIBLE_MACHINE_n1sdp = "n1sdp"
