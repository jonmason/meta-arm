COMPATIBLE_MACHINE = "qemuarm64"

DEPENDS_append_qemuarm64-sbsa = " virtual/trusted-firmware-a"

EDK2_BUILD_RELEASE_aarch64_qemuall = "1"
EDK2_ARCH_aarch64_qemuall          = "AARCH64"

EDK2_PLATFORM_qemuarm64-sbsa      = "SbsaQemu"
EDK2_PLATFORM_DSC_qemuarm64-sbsa  = "Platform/Qemu/SbsaQemu/SbsaQemu.dsc"
EDK2_BIN_NAME_qemuarm64-sbsa      = "SBSA_FLASH0.fd"

EDK2_PLATFORM_qemuarm64-secureboot      = "ArmVirtQemu-AARCH64"
EDK2_PLATFORM_DSC_qemuarm64-secureboot  = "ArmVirtPkg/ArmVirtQemu.dsc"
EDK2_BIN_NAME_qemuarm64-secureboot      = "QEMU_EFI.fd"

do_compile_prepend_qemuarm64-sbsa() {
    mkdir -p ${B}/Platform/Qemu/Sbsa/
    cp ${RECIPE_SYSROOT}/firmware/bl1.bin ${B}/Platform/Qemu/Sbsa/
    cp ${RECIPE_SYSROOT}/firmware/fip.bin ${B}/Platform/Qemu/Sbsa/
}

do_install_append_qemuarm64-sbsa() {
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/SBSA_FLASH0.fd ${D}/firmware/ovmf-tfa.bin
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/SBSA_FLASH1.fd ${D}/firmware/ovmf-uefi.bin
    /usr/bin/truncate -s 256M ${D}/firmware/ovmf*.bin
}
