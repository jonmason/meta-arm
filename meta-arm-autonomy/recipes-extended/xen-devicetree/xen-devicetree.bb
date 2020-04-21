# This recipe can be used to modify one or several DTBS to add
# entries required to declare and boot Linux as Dom0 from Xen

SRC_URI = "file://xen.dtsi.in"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "\
    file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
    "

S = "${WORKDIR}"

DESCRIPTION = "Add entries in DTB for Xen and Dom0"

# Please refer to documentation/xen-devicetree.md for documentation on those
# parameters
XEN_DEVICETREE_DEPEND ?= "virtual/kernel:do_deploy"
XEN_DEVICETREE_DTBS ?= "${KERNEL_DEVICETREE}"
XEN_DEVICETREE_XEN_BOOTARGS ?= "noreboot dom0_mem=${XEN_DEVICETREE_DOM0_MEM}"
XEN_DEVICETREE_DOM0_MEM ?= "1024M"
XEN_DEVICETREE_DOM0_BOOTARGS ?= "console=hvc0 earlycon=xen"
XEN_DEVICETREE_DOM0_ADDR ?= "0x80080000"
XEN_DEVICETREE_DOM0_SIZE ?= "0x01000000"
XEN_DEVICETREE_DTSI_MERGE ?= "xen.dtsi"

# Our package does not generate any package for the rootfs but contributes to
# deploy
inherit nopackages deploy

DEPENDS += "dtc-native"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_install[noexec] = "1"

do_deploy() {
    if [ ! -f ${WORKDIR}/xen.dtsi.in ]; then
        die "xen.dtsi.in does not exist"
    fi
    cat ${WORKDIR}/xen.dtsi.in \
        | sed -e "s,###XEN_DOM0_BOOTARGS###,${XEN_DEVICETREE_DOM0_BOOTARGS}," \
        | sed -e "s,###XEN_XEN_BOOTARGS###,${XEN_DEVICETREE_XEN_BOOTARGS}," \
        | sed -e "s,###XEN_DOM0_ADDR###,${XEN_DEVICETREE_DOM0_ADDR}," \
        | sed -e "s,###XEN_DOM0_SIZE###,${XEN_DEVICETREE_DOM0_SIZE}," \
        > ${WORKDIR}/xen.dtsi

    # Generate final dtbs
    for dtbf in ${XEN_DEVICETREE_DTBS}; do
        rdtb=`basename $dtbf`
        if [ ! -f ${DEPLOY_DIR_IMAGE}/$rdtb ]; then
            die "Wrong file in XEN_DEVICETREE_DTBS: ${DEPLOY_DIR_IMAGE}/$rdtb does not exist"
        fi
        dtc -I dtb -O dts -o ${WORKDIR}/dom0-linux.dts ${DEPLOY_DIR_IMAGE}/$rdtb

        # Add external includes
        for inc in ${XEN_DEVICETREE_DTSI_MERGE}; do
            if [ ! -f ${WORKDIR}/${inc} ]; then
                die "Wrong file in XEN_DEVICETREE_DTSI_MERGE: ${WORKDIR}/${inc} does not exist"
            fi
            echo "/include/ \"$inc\"" >> ${WORKDIR}/dom0-linux.dts
        done

        rdtbnoextn=`basename $dtbf ".dtb"`
        dtc -I dts -O dtb \
            -o ${WORKDIR}/${rdtbnoextn}-xen.dtb ${WORKDIR}/dom0-linux.dts
        install -m 644 ${rdtbnoextn}-xen.dtb ${DEPLOYDIR}/.
    done
}
do_deploy[depends] += "${XEN_DEVICETREE_DEPEND}"

addtask deploy after do_install

