COMPATIBLE_MACHINE = "qemuarm64"

DEPENDS:append:qemuarm64-sbsa = " virtual/trusted-firmware-a"

EDK2_BUILD_RELEASE:aarch64:qemuall = "1"
EDK2_ARCH:aarch64:qemuall          = "AARCH64"

EDK2_PLATFORM:qemuarm64-sbsa      = "SbsaQemu"
EDK2_PLATFORM_DSC:qemuarm64-sbsa  = "Platform/Qemu/SbsaQemu/SbsaQemu.dsc"
EDK2_BIN_NAME:qemuarm64-sbsa      = "SBSA_FLASH0.fd"

EDK2_PLATFORM:qemuarm64-secureboot      = "ArmVirtQemu-AARCH64"
EDK2_PLATFORM_DSC:qemuarm64-secureboot  = "ArmVirtPkg/ArmVirtQemu.dsc"
EDK2_BIN_NAME:qemuarm64-secureboot      = "QEMU_EFI.fd"

do_compile:prepend:qemuarm64-sbsa() {
    mkdir -p ${B}/Platform/Qemu/Sbsa/
    cp ${RECIPE_SYSROOT}/firmware/bl1.bin ${B}/Platform/Qemu/Sbsa/
    cp ${RECIPE_SYSROOT}/firmware/fip.bin ${B}/Platform/Qemu/Sbsa/
}

do_install:append:qemuarm64-sbsa() {
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/SBSA_FLASH0.fd ${D}/firmware/ovmf-tfa.bin
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/SBSA_FLASH1.fd ${D}/firmware/ovmf-uefi.bin
    /usr/bin/truncate -s 256M ${D}/firmware/ovmf*.bin
}
