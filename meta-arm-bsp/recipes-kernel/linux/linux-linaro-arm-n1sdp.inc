FILESEXTRAPATHS_prepend := "${THISDIR}/linux-linaro-arm-5.4:"

SRC_URI_append = " \
    file://0001-TMP-iommu-arm-smmu-v3-Ignore-IOPF-capabilities.patch \
    file://0002-pci_quirk-add-acs-override-for-PCI-devices.patch \
    file://0003-pcie-Add-quirk-for-the-Arm-Neoverse-N1SDP-platform.patch \
    file://0004-n1sdp-update-n1sdp-pci-quirk-for-SR-IOV-support.patch \
    file://0005-n1sdp-pcie-add-quirk-support-enabling-remote-chip-PC.patch \
    file://enable-realtek-R8169.cfg \
    file://scripts-dtc-remove-redundant-YYLOC.patch \
    "

# Referring to commit TAG N1SDP-2020.07.27
SRCREV = "84baaae9e751c058717d9702438429257f077f03"

# Use intree defconfig
KBUILD_DEFCONFIG = "defconfig"

# Since the intree defconfig in n1sdp kernel repository is not setting all the configs,
# KCONFIG_MODE is set to "alldefconfig" to properly expand the defconfig.
KCONFIG_MODE = "--alldefconfig"

COMPATIBLE_MACHINE = "n1sdp"

# RT kernel machine description
FILESEXTRAPATHS_prepend_pn-linux-linaro-arm-rt := "${THISDIR}:"
SRC_URI_append_pn-linux-linaro-arm-rt = " file://arm-platforms-kmeta;type=kmeta;name=arm-platforms-kmeta;destsuffix=arm-platforms-kmeta"

# Since we use the intree defconfig and the preempt-rt turns off some configs
# do_kernel_configcheck will display warnings. So, lets disable it.
KCONF_AUDIT_LEVEL_pn-linux-linaro-arm-rt = "0"
