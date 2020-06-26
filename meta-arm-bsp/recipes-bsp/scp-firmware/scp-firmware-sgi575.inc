# SGI575 specific SCP configurations and build instructions

#it’s a tested tag post-2.6.0
SRCREV    = "7a025658d8318e95dbab4259a8ff7834ae6d8061"
SCP_PLATFORM  = "sgi575"
SCP_LOG_LEVEL = "INFO"

COMPATIBLE_MACHINE_sgi575 = "sgi575"

do_install() {
    install -d ${D}/firmware
    install -D "${B}/product/${SCP_PLATFORM}/scp_romfw/release/bin/scp_romfw.bin" "${D}/firmware/"
    install -D "${B}/product/${SCP_PLATFORM}/scp_ramfw/release/bin/scp_ramfw.bin" "${D}/firmware/"
    install -D "${B}/product/${SCP_PLATFORM}/mcp_romfw/release/bin/mcp_romfw.bin" "${D}/firmware/"
}


PV = "2.6.0+git${SRCPV}"

