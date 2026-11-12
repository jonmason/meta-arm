COMPATIBLE_MACHINE = "tc3"
SCP_PRODUCT_GROUP = "totalcompute"
SCP_PLATFORM = "tc3"
FW_TARGETS = "scp"
FW_INSTALL = "boot runtime"

do_install() {
    install -d ${D}${FIRMWARE_DIR}
    install -m 0644 ${B}/boot/scp/bin/scp-boot.bin ${D}${FIRMWARE_DIR}/scp_boot.bin
    install -m 0644 ${B}/runtime/scp/bin/scp-runtime.bin ${D}${FIRMWARE_DIR}/scp_runtime.bin
}
