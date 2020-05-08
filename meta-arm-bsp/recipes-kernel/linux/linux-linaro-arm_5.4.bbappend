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
    "

# Referring to commit TAG N1SDP-2020.03.26
SRCREV_n1sdp  = "137cccb0843e63b031acf67d1ca4f6447b8c417c"

# Use intree defconfig
KBUILD_DEFCONFIG_n1sdp = "defconfig"

# Since the intree defconfig in n1sdp kernel repository is not setting all the configs,
# KCONFIG_MODE is set to "alldefconfig" to properly expand the defconfig.
KCONFIG_MODE_n1sdp = "--alldefconfig"

COMPATIBLE_MACHINE_n1sdp = "n1sdp"
