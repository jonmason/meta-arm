DEPENDS += 'gen-sbkeys'
DEPENDS += "sbsigntool-native"

SBSIGN_KEY = "${SBSIGN_KEYS_DIR}/db.key"
SBSIGN_CERT = "${SBSIGN_KEYS_DIR}/db.crt"
SBSIGN_TARGET_BINARY = "${B}/src/boot/systemd-boot${EFI_ARCH}.efi"

do_compile:append() {
    bbnote "Signing ${PN} binary ${SBSIGN_TARGET_BINARY} with ${SBSIGN_KEY} and ${SBSIGN_CERT}"
    ${STAGING_BINDIR_NATIVE}/sbsign \
        --key "${SBSIGN_KEY}" \
        --cert "${SBSIGN_CERT}" \
        --output  "${SBSIGN_TARGET_BINARY}.signed" \
        "${SBSIGN_TARGET_BINARY}"
    cp "${SBSIGN_TARGET_BINARY}" "${SBSIGN_TARGET_BINARY}.unsigned"
    cp "${SBSIGN_TARGET_BINARY}.signed" "${SBSIGN_TARGET_BINARY}"
}
