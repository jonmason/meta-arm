DESCRIPTION = "UEFI EDK2 Firmware for Arm reference platforms"
HOMEPAGE = "https://github.com/tianocore/edk2"

LICENSE = "BSD-2-Clause-Patent"

# EDK2
LIC_FILES_CHKSUM = "file://edk2/License.txt;md5=2b415520383f7964e96700ae12b4570a"
# EDK2 Platforms
LIC_FILES_CHKSUM += "file://edk2/edk2-platforms/License.txt;md5=2b415520383f7964e96700ae12b4570a"

SRC_URI ?= "\
    git://github.com/tianocore/edk2.git;name=edk2;destsuffix=${S}/edk2;nobranch=1 \
    git://github.com/tianocore/edk2-platforms.git;name=edk2-platforms;destsuffix=${S}/edk2/edk2-platforms;nobranch=1 \
"
SRCREV_edk2           ?= "6ff7c838d09224dd4e4c9b5b93152d8db1b19740"
SRCREV_edk2-platforms ?= "ed4cc8059ec551032f0d8b8c172e9ec19214a638"
SRCREV_FORMAT         = "edk2_edk2-platforms"

require edk2-firmware.inc
