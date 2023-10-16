require recipes-bsp/uefi/edk2-firmware_202308.bb
PROVIDES:remove = "virtual/bootloader"

# iNeoverse V2 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "SgiMmStandalone"
EDK2_PLATFORM_DSC  = "Platform/ARM/SgiPkg/PlatformStandaloneMm2.dsc"
EDK2_BIN_NAME      = "BL32_AP_MM.fd"

COMPATIBLE_MACHINE = "rd-v2"

do_install() {
    install -d ${D}/firmware
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/${EDK2_BIN_NAME} ${D}/firmware/mm_standalone.bin
}
