SUMMARY = "OP-TEE Client API"
DESCRIPTION = "Open Portable Trusted Execution Environment - Normal World Client side of the TEE"
HOMEPAGE = "https://www.op-tee.org/"

LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=69663ab153298557a59c67a60a743e5b"

require optee.inc

inherit python3native systemd update-rc.d

SRC_URI = " \
    git://github.com/OP-TEE/optee_client.git \
    file://tee-supplicant.service \
    file://tee-supplicant.sh \
"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

EXTRA_OEMAKE = "O=${B}"

do_compile() {
    cd ${S}
    oe_runmake
}
do_compile[cleandirs] = "${B}"

do_install() {
    cd ${S}
    oe_runmake install

    install -D -p -m0755 ${B}/export/usr/sbin/tee-supplicant ${D}${sbindir}/tee-supplicant

    install -D -p -m0644 ${B}/export/usr/lib/libteec.so.1.0 ${D}${libdir}/libteec.so.1.0
    ln -sf libteec.so.1.0 ${D}${libdir}/libteec.so
    ln -sf libteec.so.1.0 ${D}${libdir}/libteec.so.1

    install -d ${D}${includedir}
    install -p -m0644 ${B}/export/usr/include/*.h ${D}${includedir}

    install -D -p -m0644 ${WORKDIR}/tee-supplicant.service ${D}${systemd_system_unitdir}/tee-supplicant.service

    install -D -p -m0755 ${WORKDIR}/tee-supplicant.sh ${D}${sysconfdir}/init.d/tee-supplicant

    sed -i -e s:@sysconfdir@:${sysconfdir}:g \
           -e s:@sbindir@:${sbindir}:g \
              ${D}${systemd_system_unitdir}/tee-supplicant.service \
              ${D}${sysconfdir}/init.d/tee-supplicant
}

SYSTEMD_SERVICE_${PN} = "tee-supplicant.service"

INITSCRIPT_PACKAGES = "${PN}"

INITSCRIPT_NAME_${PN} = "tee-supplicant"
INITSCRIPT_PARAMS_${PN} = "start 10 1 2 3 4 5 . stop 90 0 6 ."


