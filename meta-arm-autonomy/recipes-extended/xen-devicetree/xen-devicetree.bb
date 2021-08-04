# This recipe can be used to modify one or several DTBS to add
# entries required to declare and boot Linux as Dom0 from Xen

SRC_URI = "file://xen.dtsi.in"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "\
    file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
    "

S = "${WORKDIR}"

DESCRIPTION = "Add entries in DTB for Xen and Dom0"

# Please refer to documentation/xen-devicetree.md for documentation on these
# customizable parameters
# kernel size is passed to xen via xen.dtb so we need to add
# 'virtual/kernel:do_deploy' as a dependency
XEN_DEVICETREE_DEPEND:append = " virtual/kernel:do_deploy"
XEN_DEVICETREE_DTBS ?= "${KERNEL_DEVICETREE}"
XEN_DEVICETREE_XEN_BOOTARGS ?= "noreboot dom0_mem=${XEN_DEVICETREE_DOM0_MEM}"
XEN_DEVICETREE_DOM0_MEM ?= "1024M,max:1024M"
XEN_DEVICETREE_DOM0_BOOTARGS ?= "console=hvc0 earlycon=xen"
XEN_DEVICETREE_DOM0_ADDR ?= "0x80080000"
XEN_DEVICETREE_DOM0_SIZE ?= "0x01000000"
XEN_DEVICETREE_DTSI_MERGE ?= "xen.dtsi"

# Our package does not generate any packages for the rootfs, but instead
# contributes to deploy
inherit nopackages deploy

DEPENDS += "dtc-native"
PACKAGE_ARCH = "${MACHINE_ARCH}"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_install[noexec] = "1"

# Validate xen devicetree variables
python __anonymous() {

    # Compare values of a list of variables to a regex pattern
    def validate_type(pattern, var_list):
        for varname in var_list:
            if d.getVar(varname):
                if not pattern.match(d.getVar(varname)):
                    raise bb.parse.SkipRecipe(d.getVar(varname) + "' is not a valid value for " + varname + "!")
            else:
                raise bb.parse.SkipRecipe('Required variable ' + varname + ' is empty!')

    import re

    num_vars_to_check = ['XEN_DEVICETREE_DOM0_ADDR', 'XEN_DEVICETREE_DOM0_SIZE']
    size_vars_to_check = ['XEN_DEVICETREE_DOM0_MEM']

    num_pattern = re.compile(r'((0x[0-9a-fA-F]+)|[0-9]+)$')
    size_pattern = re.compile(r'[0-9]+[MG](,max:[0-9]+[MG])?$')

    validate_type(num_pattern, num_vars_to_check)
    validate_type(size_pattern, size_vars_to_check)
}

do_deploy() {
    if [ ! -f ${WORKDIR}/xen.dtsi.in ]; then
        die "xen.dtsi.in does not exist"
    fi
    cat ${WORKDIR}/xen.dtsi.in \
        | sed -e "s?###XEN_DOM0_BOOTARGS###?${XEN_DEVICETREE_DOM0_BOOTARGS}?" \
        | sed -e "s?###XEN_XEN_BOOTARGS###?${XEN_DEVICETREE_XEN_BOOTARGS}?" \
        | sed -e "s?###XEN_DOM0_ADDR###?${XEN_DEVICETREE_DOM0_ADDR}?" \
        | sed -e "s?###XEN_DOM0_SIZE###?${XEN_DEVICETREE_DOM0_SIZE}?" \
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
do_deploy[prefuncs] += "calc_xen_dtb_dom0_size"

addtask deploy after do_install

python calc_xen_dtb_dom0_size() {
    from math import ceil
    size = 0
    if d.getVar('KERNEL_IMAGE_MAXSIZE'):
        bb.note('size calculation based on KERNEL_IMAGE_MAXSIZE')
        size = int(d.getVar('KERNEL_IMAGE_MAXSIZE')) * 1024
    else:
        kernel = os.path.realpath(d.getVar('DEPLOY_DIR_IMAGE') + '/' +\
                 d.getVar('KERNEL_IMAGETYPE'))
        size = os.stat(kernel).st_size
        bb.note('size calculation based on kernel Image file: %s' % kernel)

    bb.note('size in bytes: %d' % size)
    # Ceil to MiB
    size_required = ceil(size / (2 ** 20)) * (2 ** 20)
    xen_devicetree_dom0_size = d.getVar('XEN_DEVICETREE_DOM0_SIZE')
    if xen_devicetree_dom0_size[:2] == "0x":
        size_defined = int(xen_devicetree_dom0_size, 16)
    else:
        size_defined = int(xen_devicetree_dom0_size)

    if size_required > size_defined:
        bb.note ("Wrong kernel size setting inside xen dtb!\n"\
                 "Required:\t%(req)d (%(req)#010X)\n"\
                 "Requested:\t%(def)d (%(def)#010X)"\
                 % {"req": size_required, "def": size_defined})
        bb.note ("Overriding XEN_DEVICETREE_DOM0_SIZE with "\
                 "%(req)d (%(req)#010X)" % {"req": size_required})
        d.setVar('XEN_DEVICETREE_DOM0_SIZE', hex(size_required))
}
