SUMMARY = "OP-TEE Client API"
DESCRIPTION = "Open Portable Trusted Execution Environment - Normal World Client side of the TEE"
HOMEPAGE = "https://www.op-tee.org/"

LICENSE = "BSD-2-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=69663ab153298557a59c67a60a743e5b"

inherit systemd update-rc.d cmake useradd

SRC_URI = " \
    git://github.com/OP-TEE/optee_client.git;branch=master;protocol=https \
    file://tee-supplicant.sh \
"

UPSTREAM_CHECK_GITTAGREGEX = "^(?P<pver>\d+(\.\d+)+)$"

S = "${WORKDIR}/git"

EXTRA_OECMAKE = " \
    -DBUILD_SHARED_LIBS=ON \
"
EXTRA_OECMAKE:append:toolchain-clang = " -DCFG_WERROR=0"

do_install:append() {
    # installed by default
    if ! ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'true', 'false', d)}; then
        rm -rf ${D}${libdir}/systemd
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'sysvinit', 'true', 'false', d)}; then
        install -D -p -m0755 ${UNPACKDIR}/tee-supplicant.sh ${D}${sysconfdir}/init.d/tee-supplicant
        sed -i -e s:@sysconfdir@:${sysconfdir}:g \
               -e s:@sbindir@:${sbindir}:g \
                  ${D}${sysconfdir}/init.d/tee-supplicant
    fi
    install -o teesuppl -g teesuppl -m 0700 -d ${D}${localstatedir}/lib/tee
}

SYSTEMD_SERVICE:${PN} = "tee-supplicant@.service"

INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME:${PN} = "tee-supplicant"
INITSCRIPT_PARAMS:${PN} = "start 10 1 2 3 4 5 . stop 90 0 6 ."

# Users and groups:
# tee group to access /dev/tee*
# teepriv group to acess /dev/teepriv*, only tee-supplicant
# teesuppl user and group teesuppl to run tee-supplicant
USERADD_PACKAGES = "${PN}"
GROUPADD_PARAM:${PN} = "--system tee; --system teepriv; --system teesuppl"
USERADD_PARAM:${PN} = "--system -g teesuppl --groups teepriv --home-dir ${localstatedir}/lib/tee -M --shell /sbin/nologin teesuppl;"
