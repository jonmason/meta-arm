# Xenguest mkimage recipe
#
# xenguest-mkimage is a tool to create/modify images to be used as xen guests
# Produced images contains a xen configuration and several optional components
# (kernel, device-tree, disk definition and files, init scripts) which all
# together fully define a full xen guest

DESCRIPTION = "Xenguest mkimage tool"
LICENSE = "MIT"

SRC_URI = "file://xenguest-mkimage"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

S = "${WORKDIR}"

# Can be built native also to produce xenguest images during Yocto build
BBCLASSEXTEND = "native"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    install -d -m 755 ${D}${bindir}
    install -m 755 xenguest-mkimage ${D}${bindir}/.
}

# We need bash and tar
RDEPENDS_${PN} = "bash tar"
FILES_${PN} = "${bindir}/xenguest-mkimage"

