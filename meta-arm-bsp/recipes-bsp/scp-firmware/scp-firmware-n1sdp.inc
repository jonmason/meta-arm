# N1SDP specific SCP configurations and build instructions

SCP_PLATFORM  = "n1sdp"
SCP_LOG_LEVEL = "INFO"

COMPATIBLE_MACHINE_n1sdp = "n1sdp"

DEPENDS += "fiptool-native"
DEPENDS += "virtual/trusted-firmware-a"

do_install_append() {
   fiptool \
       create \
       --scp-fw "${D}/firmware/scp_ramfw.bin" \
       --soc-fw "${RECIPE_SYSROOT}/firmware/bl31.bin" \
       "scp_fw.bin"

   fiptool \
       create \
       --blob uuid=54464222-a4cf-4bf8-b1b6-cee7dade539e,file="${D}/firmware/mcp_ramfw.bin" \
       "mcp_fw.bin"

   install "scp_fw.bin" "${D}/firmware/scp_fw.bin"
   install "mcp_fw.bin" "${D}/firmware/mcp_fw.bin"

   ln -sf "scp_romfw.bin" "${D}/firmware/scp_rom.bin"
   ln -sf "mcp_romfw.bin" "${D}/firmware/mcp_rom.bin"
}
