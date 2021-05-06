# Platform dependent parameters

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# Add a dtb snippet to turn off iommu in dom0 on Juno board
SRC_URI_append_juno = " file://xen-juno.dtsi"
XEN_DEVICETREE_DTSI_MERGE_append_juno = " xen-juno.dtsi"

# Add a dtb snippet to remove pmu and iommu in dom0 on N1SDP
SRC_URI_append_n1sdp = " file://xen-n1sdp.dtsi"
XEN_DEVICETREE_DTSI_MERGE_append_n1sdp = " xen-n1sdp.dtsi"
# For N1SDP, the XEN_DEVICETREE_DEPEND and XEN_DEVICETREE_DTBS variables are
# being set in meta-arm-autonomy/dynamic-layers/meta-arm-bsp/conf/machine/n1sdp-extra-settings.inc

# Board specific configs
XEN_DEVICETREE_DOM0_BOOTARGS_append_juno = " root=/dev/sda1 rootwait"
XEN_DEVICETREE_XEN_BOOTARGS_append_juno = " console=dtuart dtuart=serial0 bootscrub=0 iommu=no"

XEN_DEVICETREE_DOM0_BOOTARGS_append_n1sdp = " root=/dev/sda2 rootwait"
XEN_DEVICETREE_XEN_BOOTARGS_append_n1sdp = " console=dtuart dtuart=serial0 bootscrub=0 iommu=no"

XEN_DEVICETREE_DOM0_BOOTARGS_append_fvp-base = " root=/dev/vda1"
XEN_DEVICETREE_XEN_BOOTARGS_append_fvp-base = " console=dtuart dtuart=serial0 bootscrub=0"
