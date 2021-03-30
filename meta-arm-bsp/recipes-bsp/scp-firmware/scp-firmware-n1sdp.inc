# N1SDP specific SCP configurations and build instructions

SCP_PLATFORM  = "n1sdp"
SCP_LOG_LEVEL = "INFO"

LIC_FILES_CHKSUM = "file://license.md;beginline=5;md5=9db9e3d2fb8d9300a6c3d15101b19731 \
                    file://contrib/cmsis/git/LICENSE.txt;md5=e3fc50a88d0a364313df4b21ef20c29e"

SRCREV  = "6c15afb1b37d0728482c598b063cd69bfc733e93"
PV = "2.7.0+git${SRCPV}"

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
