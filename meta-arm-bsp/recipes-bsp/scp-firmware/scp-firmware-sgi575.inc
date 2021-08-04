# SGI575 specific SCP configurations and build instructions

SCP_PLATFORM  = "sgi575"
SCP_LOG_LEVEL = "INFO"

COMPATIBLE_MACHINE:sgi575 = "sgi575"

do_install() {
    install -d ${D}/firmware
    install -D "${B}/product/${SCP_PLATFORM}/scp_romfw/release/bin/scp_romfw.bin" "${D}/firmware/"
    install -D "${B}/product/${SCP_PLATFORM}/scp_ramfw/release/bin/scp_ramfw.bin" "${D}/firmware/"
    install -D "${B}/product/${SCP_PLATFORM}/mcp_romfw/release/bin/mcp_romfw.bin" "${D}/firmware/"
}
