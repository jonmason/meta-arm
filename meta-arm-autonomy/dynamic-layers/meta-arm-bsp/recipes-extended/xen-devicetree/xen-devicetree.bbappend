# Platform dependent parameters

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Add a dtb snippet to turn off iommu in dom0 on Juno board
SRC_URI:append:juno = " file://xen-juno.dtsi"
XEN_DEVICETREE_DTSI_MERGE:append:juno = " xen-juno.dtsi"

# Add a dtb snippet to remove pmu and iommu in dom0 on N1SDP
SRC_URI:append:n1sdp = " file://xen-n1sdp.dtsi"
XEN_DEVICETREE_DTSI_MERGE:append:n1sdp = " xen-n1sdp.dtsi"
# For N1SDP, the XEN_DEVICETREE_DEPEND and XEN_DEVICETREE_DTBS variables are
# being set in meta-arm-autonomy/dynamic-layers/meta-arm-bsp/conf/machine/n1sdp-extra-settings.inc

# Board specific configs
XEN_DEVICETREE_DOM0_BOOTARGS:append:juno = " root=/dev/sda1 rootwait"
XEN_DEVICETREE_XEN_BOOTARGS:append:juno = " console=dtuart dtuart=serial0 bootscrub=0 iommu=no"

XEN_DEVICETREE_DOM0_BOOTARGS:append:n1sdp = " root=/dev/sda2 rootwait"
XEN_DEVICETREE_XEN_BOOTARGS:append:n1sdp = " console=dtuart dtuart=serial0 bootscrub=0 iommu=no"

XEN_DEVICETREE_DOM0_BOOTARGS:append:fvp-base = " root=/dev/vda1"
XEN_DEVICETREE_XEN_BOOTARGS:append:fvp-base = " console=dtuart dtuart=serial0 bootscrub=0"
