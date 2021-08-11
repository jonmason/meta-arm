# Recipe to handle xenguest network configuration
DESCRIPTION = "Xenguest Network"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

S = "${WORKDIR}"

# Please refer to documentation/xenguest-network-bridge.md for documentation on
# the parameters available for customization
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
    file://xenguest-network-init-post.sh \
    file://kea-dhcp4.conf \
    file://kea-restore-default-config \
    "
PACKAGES =+ "${PN}-kea-dhcp4"

# Bridge configurator needs to run before S01networking init script
# Prefix with a_ to make sure it is executed in runlevel 01 before others
# run start script before ifupdown and run stop script after ifupdown
INITSCRIPT_PACKAGES = "${PN} ${PN}-kea-dhcp4"
INITSCRIPT_NAME:${PN} = "a_xenguest-network-bridge"
INITSCRIPT_PARAMS:${PN} = "start 01 2 3 4 5 . stop 81 0 1 6 ."

# Kea configuration needs to be restored before kea init scripts:
# Kea dhcp4 server is 30, so lets use 20, to have higher priority
INITSCRIPT_NAME:${PN}-kea-dhcp4 = "kea-restore-default-config"
INITSCRIPT_PARAMS:${PN}-kea-dhcp4 = "defaults 20"

inherit allarch update-rc.d

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
        ${D}${sysconfdir}/init.d/${INITSCRIPT_NAME:${PN}}
    install -d -m 755 ${D}${sysconfdir}/network/interfaces.d
    install -m 755 ${WORKDIR}/xenguest-network-bridge.cfg \
        ${D}${sysconfdir}/network/interfaces.d/.
    install -d -m 755 ${D}${sysconfdir}/xenguest/init.pre
    install -m 755 ${WORKDIR}/network-bridge.sh \
        ${D}${sysconfdir}/xenguest/init.pre/.

    install -d ${D}${sysconfdir}/xen/scripts/vif-post.d
    install -m 755 ${WORKDIR}/00-vif-xenguest.hook \
        ${D}${sysconfdir}/xen/scripts/vif-post.d/.

    install -d -m 755 ${D}${sysconfdir}/xenguest/init.post
    install -m 755 ${WORKDIR}/xenguest-network-init-post.sh \
        ${D}${sysconfdir}/xenguest/init.post/.

    install -m 755 ${WORKDIR}/kea-restore-default-config \
        ${D}${sysconfdir}/init.d/.
    install -d -m 755 ${D}${sysconfdir}/kea/
    install -m 755 ${WORKDIR}/kea-dhcp4.conf \
        ${D}${sysconfdir}/kea/kea-dhcp4.conf.original
}

RDEPENDS:${PN} += "bridge-utils \
                   iptables \
                   kea \
                   ${PN}-kea-dhcp4 \
                   kernel-module-xt-tcpudp \
                   kernel-module-xt-physdev \
                   kernel-module-xt-comment \
                   kernel-module-xt-nat \
                   kernel-module-xt-masquerade \
                  "
FILES:${PN} += "${sysconfdir}/network/interfaces.d/xenguest-network-bridge.cfg"
FILES:${PN} += "${sysconfdir}/xenguest/init.pre/network-bridge.sh"
FILES:${PN} += "${sysconfdir}/xen/scripts/vif-post.d/00-vif-xenguest.hook"

FILES:${PN}-kea-dhcp4 = "${sysconfdir}/kea/kea-dhcp4.conf.original"
FILES:${PN}-kea-dhcp4 += "${sysconfdir}/init.d/${INITSCRIPT_NAME:${PN}-kea-dhcp4}"
FILES:${PN}-kea-dhcp4 += "${sysconfdir}/xenguest/init.post/xenguest-network-init-post.sh"
