
SRC_URI_TRUSTED_FIRMWARE_M ?= "git://git.trustedfirmware.org/TF-M/trusted-firmware-m.git;protocol=https"
SRC_URI = "${SRC_URI_TRUSTED_FIRMWARE_M};branch=${SRCBRANCH}"
# Use the wrapper script from TF-Mv1.7.0
SRCBRANCH ?= "master"
SRCREV = "b725a1346cdb9ec75b1adcdc4c84705881e8fd4e"

LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://license.rst;md5=07f368487da347f3c7bd0fc3085f3afa"

S = "${WORKDIR}/git"

inherit native

# See bl2/ext/mcuboot/scripts/requirements.txt
RDEPENDS:${PN} = "\
    python3-cryptography-native \
    python3-pyasn1-native \
    python3-pyyaml-native \
    python3-cbor2-native \
    python3-imgtool-native \
    python3-click-native \
"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    install -d ${D}/${libdir}
    cp -rf ${S}/bl2/ext/mcuboot/scripts/ ${D}/${libdir}/tfm-scripts
    cp -rf ${S}/bl2/ext/mcuboot/*.pem ${D}/${libdir}/tfm-scripts
}
FILES:${PN} = "${libdir}/tfm-scripts"
