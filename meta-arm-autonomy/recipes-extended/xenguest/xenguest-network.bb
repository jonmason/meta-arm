# Recipe to handle xenguest network configuration
DESCRIPTION = "Xenguest Network"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

S = "${WORKDIR}"

# Please refer to documentation/xenguest-network-bridge.md for documentation on
# those parameters
XENGUEST_NETWORK_BRIDGE_NAME ?= "xenbr0"

# The XENGUEST_NETWORK_BRIDGE_MEMBERS should be set in a machine.conf
# or bbappend file.
#XENGUEST_NETWORK_BRIDGE_MEMBERS ?= "eth0"

XENGUEST_NETWORK_BRIDGE_CONFIG ?= "xenguest-network-bridge-dhcp.cfg.in"

SRC_URI = " \
    file://xenguest-network-bridge.in \
    file://xenguest-network-bridge-dhcp.cfg.in \
    file://network-bridge.sh.in \
    file://00-vif-xenguest.hook \
    "

# Bridge configurator needs to run before S01networking init script
# Prefix with a_ to make sure it is executed in runlevel 01 before others
INITSCRIPT_NAME = "a_xenguest-network-bridge"
INITSCRIPT_PARAMS = "defaults 01"

inherit update-rc.d

do_install() {
    cat ${WORKDIR}/xenguest-network-bridge.in \
       | sed -e "s,###BRIDGE_MEMBERS###,${XENGUEST_NETWORK_BRIDGE_MEMBERS}," \
       | sed -e "s,###BRIDGE_NAME###,${XENGUEST_NETWORK_BRIDGE_NAME}," \
       > ${WORKDIR}/xenguest-network-bridge
    cat ${WORKDIR}/${XENGUEST_NETWORK_BRIDGE_CONFIG} \
       | sed -e "s,###BRIDGE_NAME###,${XENGUEST_NETWORK_BRIDGE_NAME}," \
       > ${WORKDIR}/xenguest-network-bridge.cfg
    cat ${WORKDIR}/network-bridge.sh.in \
       | sed -e "s,###BRIDGE_NAME###,${XENGUEST_NETWORK_BRIDGE_NAME}," \
       > ${WORKDIR}/network-bridge.sh
    install -d -m 755 ${D}${sysconfdir}/init.d
    install -m 755 ${WORKDIR}/xenguest-network-bridge \
        ${D}${sysconfdir}/init.d/${INITSCRIPT_NAME}
    install -d -m 755 ${D}${sysconfdir}/network/interfaces.d
    install -m 755 ${WORKDIR}/xenguest-network-bridge.cfg \
        ${D}${sysconfdir}/network/interfaces.d/.
    install -d -m 755 ${D}${sysconfdir}/xenguest/init.pre
    install -m 755 ${WORKDIR}/network-bridge.sh \
        ${D}${sysconfdir}/xenguest/init.pre/.

    install -d ${D}${sysconfdir}/xen/scripts/vif-post.d
    install -m 755 ${WORKDIR}/00-vif-xenguest.hook \
        ${D}${sysconfdir}/xen/scripts/vif-post.d/.
}

RDEPENDS_${PN} += "bridge-utils \
                   iptables \
                   dhcp-server \
                   kernel-module-xt-tcpudp \
                   kernel-module-xt-physdev \
                   kernel-module-xt-comment \
                   kernel-module-xt-nat \
                  "
FILES_${PN} += "${sysconfdir}/network/interfaces.d/xenguest-network-bridge.cfg"
FILES_${PN} += "${sysconfdir}/xenguest/init.pre/network-bridge.sh"
FILES_${PN} += "${sysconfdir}/xen/scripts/vif-post.d/00-vif-xenguest.hook"
