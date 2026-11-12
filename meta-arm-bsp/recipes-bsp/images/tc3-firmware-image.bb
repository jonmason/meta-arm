SUMMARY = "Bootable firmware flash image for the TC3 FVP"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

COMPATIBLE_MACHINE = "tc3"

FILESEXTRAPATHS:prepend := "${THISDIR}/../trusted-firmware-a/files/tc:"
SRC_URI = "file://generate_metadata.py"

DEPENDS = "trusted-firmware-a trusted-firmware-m scp-firmware \
           fiptool-tc3-native trusted-firmware-m-scripts-native \
           util-linux-native"

inherit firmware python3native

S = "${UNPACKDIR}"
B = "${WORKDIR}/build"
do_configure[noexec] = "1"
do_compile[cleandirs] = "${B}"

do_compile() {
    rse="${RECIPE_SYSROOT}/firmware/trusted-firmware-m"
    tfa="${RECIPE_SYSROOT}/firmware/trusted-firmware-a"
    scp="${RECIPE_SYSROOT}/firmware/scp-firmware"
    scripts="${STAGING_LIBDIR_NATIVE}/tfm-scripts"

    cat > ${B}/ap_bl1_layout.h <<EOF
enum image_attributes {
    RE_IMAGE_LOAD_ADDRESS = 0x70000000,
    RE_SIGN_BIN_SIZE = 0x20000,
};
EOF
    cat > ${B}/scp_bl1_layout.h <<EOF
enum image_attributes {
    RE_IMAGE_LOAD_ADDRESS = 0x71000000,
    RE_SIGN_BIN_SIZE = 0x20000,
};
EOF

    cd "$scripts"
    python3 -m bl2.wrapper -v 1.5.0 --layout ${B}/ap_bl1_layout.h \
        -k root-RSA-3072.pem --public-key-format full --align 1 \
        --pad --pad-header -H 0x2000 -s 1 \
        "$tfa/bl1.bin" ${B}/signed_bl1-tc.bin
    python3 -m bl2.wrapper -v 1.5.0 --layout ${B}/scp_bl1_layout.h \
        -k root-RSA-3072.pem --public-key-format full --align 1 \
        --pad --pad-header -H 0x2000 -s 1 \
        "$scp/scp_boot.bin" ${B}/signed_scp-boot.bin

    cp "$tfa/fip.bin" ${B}/fip-tc.bin
    fiptool update --align 8192 --rse-bl2 "$rse/bl2_signed.bin" ${B}/fip-tc.bin
    fiptool update --align 8192 --rse-scp-bl1 ${B}/signed_scp-boot.bin ${B}/fip-tc.bin
    fiptool update --align 8192 --rse-ap-bl1 ${B}/signed_bl1-tc.bin ${B}/fip-tc.bin
    if [ -f "$rse/tfm_s_sic_tables_signed.bin" ]; then
        fiptool update --align 8192 --rse-s "$rse/tfm_s_encrypted.bin" ${B}/fip-tc.bin
        fiptool update --align 8192 --rse-sic-tables-s "$rse/tfm_s_sic_tables_signed.bin" ${B}/fip-tc.bin
    else
        fiptool update --align 8192 --rse-s "$rse/tfm_s_signed.bin" ${B}/fip-tc.bin
    fi

    fip_type_uuid=$(uuidgen --sha1 --namespace @dns --name fip_type_uuid)
    metadata_type_uuid="8a7a84a0-8387-40f6-ab41-a8b9a5a60d23"
    location_uuid=$(uuidgen)
    fip_a_uuid=$(uuidgen)
    fip_b_uuid=$(uuidgen)
    : > ${B}/metadata.bin
    python3 ${UNPACKDIR}/generate_metadata.py \
        --metadata_file ${B}/metadata.bin \
        --img_type_uuids "$fip_type_uuid" \
        --location_uuids "$location_uuid" \
        --img_uuids "$fip_a_uuid" "$fip_b_uuid"

    size=`stat -c %s ${B}/fip-tc.bin`
    fip_sectors=`expr \( $size + 1048575 \) / 1048576 \* 2048`
    start_a=2048
    start_b=`expr $start_a + $fip_sectors`
    start_meta=`expr $start_b + $fip_sectors`
    start_meta_backup=`expr $start_meta + 16`
    total_sectors=`expr $start_meta_backup + 16 + 33`
    total_bytes=`expr $total_sectors \* 512`
    truncate -s $total_bytes ${B}/fip_gpt-tc.bin
    cat > ${B}/partitions.sfdisk <<EOF
label: gpt
label-id: $location_uuid
unit: sectors
start=$start_a, size=$fip_sectors, type=$fip_type_uuid, uuid=$fip_a_uuid, name=FIP_A
start=$start_b, size=$fip_sectors, type=$fip_type_uuid, uuid=$fip_b_uuid, name=FIP_B
start=$start_meta, size=1, type=$metadata_type_uuid, name=FWU-Metadata
start=$start_meta_backup, size=1, type=$metadata_type_uuid, name=Bkup-FWU-Metadata
EOF
    sfdisk --wipe always ${B}/fip_gpt-tc.bin < ${B}/partitions.sfdisk
    dd if=${B}/fip-tc.bin of=${B}/fip_gpt-tc.bin bs=512 seek=${start_a} conv=notrunc
    dd if=${B}/fip-tc.bin of=${B}/fip_gpt-tc.bin bs=512 seek=${start_b} conv=notrunc
    dd if=${B}/metadata.bin of=${B}/fip_gpt-tc.bin bs=512 seek=${start_meta} conv=notrunc
    dd if=${B}/metadata.bin of=${B}/fip_gpt-tc.bin bs=512 seek=${start_meta_backup} conv=notrunc
}

do_install() {
    install -d ${D}${FIRMWARE_DIR}
    install -m 0644 ${B}/fip-tc.bin ${D}${FIRMWARE_DIR}/
    install -m 0644 ${B}/fip_gpt-tc.bin ${D}${FIRMWARE_DIR}/
}
