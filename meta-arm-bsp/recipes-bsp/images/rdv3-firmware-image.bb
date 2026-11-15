SUMMARY = "RDV3 firmware images for the FVP"
LICENSE = "MIT AND Apache-2.0 AND BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
                    file://${UNPACKDIR}/tfm/license.rst;md5=07f368487da347f3c7bd0fc3085f3afa \
                    file://${UNPACKDIR}/mcuboot/LICENSE;md5=b6ee33f1d12a5e6ee3de1e82fb51eeb8"

SRC_URI = "file://assemble-rdv3.py \
           git://gitlab.arm.com/infra-solutions/reference-design/platsw/trusted-firmware-m.git;protocol=https;branch=refinfra;name=tfm;destsuffix=tfm \
           git://github.com/mcu-tools/mcuboot.git;protocol=https;branch=main;name=mcuboot;destsuffix=mcuboot \
           git://gitlab.arm.com/infra-solutions/reference-design/scripts/model-scripts.git;protocol=https;branch=refinfra;name=model-scripts;destsuffix=model-scripts"
SRCREV_tfm = "2c1ffad021790eca77b7e0105223475441907e87"
SRCREV_mcuboot = "6071ceb1d0d955b6ff4745499a0ff3ac7d79f24b"
SRCREV_model-scripts = "764298dfa5f79cfb9159a3201ba2f65e0b59c359"
SRCREV_FORMAT = "tfm_mcuboot_model-scripts"
S = "${UNPACKDIR}/tfm"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

inherit deploy python3native

DEPENDS = "trusted-firmware-m trusted-firmware-a virtual/control-processor-firmware \
           python3-click-native python3-cryptography-native python3-intelhex-native \
           python3-cbor2-native python3-pyyaml-native"
do_deploy[depends] += "trusted-firmware-m:do_deploy trusted-firmware-a:do_deploy scp-firmware:do_deploy"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "rdv3"

do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_install[noexec] = "1"

do_deploy() {
    install -d ${DEPLOYDIR}
    install -m 0644 ${UNPACKDIR}/model-scripts/rdinfra/platforms/rdv3/example_pcie_hierarchy_*.json ${DEPLOYDIR}/
    python3 ${UNPACKDIR}/assemble-rdv3.py \
        --deploy-dir ${DEPLOY_DIR_IMAGE} \
        --tfm-scripts ${UNPACKDIR}/tfm/bl2/ext/mcuboot/scripts \
        --mcuboot-scripts ${UNPACKDIR}/mcuboot/scripts \
        --output-dir ${DEPLOYDIR}
}
addtask deploy after do_install
