DESCRIPTION = "Firmware for SCP and MCP software reference implementation"
HOMEPAGE = "https://github.com/ARM-software/SCP-firmware"

LICENSE = "BSD-3-Clause & Apache-2.0"

# SCP
LIC_FILES_CHKSUM = "file://license.md;beginline=5;md5=9db9e3d2fb8d9300a6c3d15101b19731"
# CMSIS
LIC_FILES_CHKSUM += "file://cmsis/LICENSE.txt;md5=e3fc50a88d0a364313df4b21ef20c29e"

SRC_URI = "\
    git://github.com/ARM-software/SCP-firmware.git;protocol=https;name=scp;destsuffix=src;nobranch=1 \
    git://github.com/ARM-software/CMSIS_5.git;protocol=https;name=cmsis;destsuffix=src/cmsis;lfs=0;nobranch=1 \
    file://0001-tools-gen_module_code-atomically-rewrite-the-generat.patch \
"

PV            = "2.6+git${SRCPV}"
SRCREV_scp    = "fd7c83561a7d76c7681d5d017fb23aa3664c028c"
SRCREV_cmsis  = "80cc44bba16cb4c8f495b7aa9709d41ac50e9529"
SRCREV_FORMAT = "scp_cmsis"

require scp-firmware.inc
