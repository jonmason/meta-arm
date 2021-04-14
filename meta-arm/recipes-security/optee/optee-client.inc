SUMMARY = "OP-TEE Client API"
DESCRIPTION = "Open Portable Trusted Execution Environment - Normal World Client side of the TEE"
HOMEPAGE = "https://www.op-tee.org/"

LICENSE = "BSD-2-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=69663ab153298557a59c67a60a743e5b"

inherit systemd update-rc.d cmake

SRC_URI = " \
    git://github.com/OP-TEE/optee_client.git \
    file://tee-supplicant.service \
    file://tee-supplicant.sh \
"

UPSTREAM_CHECK_GITTAGREGEX = "^(?P<pver>\d+(\.\d+)+)$"

S = "${WORKDIR}/git"

EXTRA_OECMAKE = " \
    -DBUILD_SHARED_LIBS=ON \
    -DCFG_TEE_FS_PARENT_PATH='${localstatedir}/lib/tee' \
"
EXTRA_OECMAKE_append_toolchain-clang = " -DCFG_WERROR=0"

do_install_append() {
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
