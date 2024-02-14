SUMARY = "Corstone1000 platform Image"
DESCRIPTION = "This is the main image which is the container of all the binaries \
               generated for the Corstone1000 platform."
LICENSE = "MIT"

COMPATIBLE_MACHINE = "corstone1000"

inherit image
inherit tfm_sign_image
inherit  uefi_capsule

PACKAGE_INSTALL = ""

IMAGE_FSTYPES += "wic uefi_capsule"

UEFI_FIRMWARE_BINARY = "${PN}-${MACHINE}.${CAPSULE_IMGTYPE}"
UEFI_CAPSULE_CONFIG = "${THISDIR}/files/${PN}-capsule-update-image.json"
CAPSULE_IMGTYPE = "wic"

# TF-X settings for signing host images
RE_LAYOUT_WRAPPER_VERSION = "0.0.7"
TFM_SIGN_PRIVATE_KEY = "${libdir}/tfm-scripts/root-RSA-3072_1.pem"
RE_IMAGE_OFFSET = "0x1000"

do_sign_images() {
    # Sign TF-A BL2
    sign_host_image ${RECIPE_SYSROOT}/firmware/${TFA_BL2_BINARY} \
        ${TFA_BL2_RE_IMAGE_LOAD_ADDRESS} ${TFA_BL2_RE_SIGN_BIN_SIZE}

    # Update BL2 in the FIP image
    cp ${RECIPE_SYSROOT}/firmware/${TFA_FIP_BINARY} .
    fiptool update --tb-fw \
        ${TFM_IMAGE_SIGN_DEPLOY_DIR}/signed_${TFA_BL2_BINARY} \
        ${TFM_IMAGE_SIGN_DIR}/${TFA_FIP_BINARY}

    # Sign the FIP image
    sign_host_image ${TFM_IMAGE_SIGN_DIR}/${TFA_FIP_BINARY} \
        ${TFA_FIP_RE_IMAGE_LOAD_ADDRESS} ${TFA_FIP_RE_SIGN_BIN_SIZE}
}
do_sign_images[depends] = "\
    trusted-firmware-a:do_populate_sysroot \
    fiptool-native:do_populate_sysroot \
    "
