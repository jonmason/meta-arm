#FIXME - qemuarm*-secureboot's can probably use the qemuarm/64 fallthroughs and only specify the necessary below.  Defining everything now just in case this is wrong
COMPATIBLE_MACHINE:qemuarm64-secureboot = "qemuarm64-secureboot"
EDK2_PLATFORM:qemuarm64-secureboot      = "ArmVirtQemu-AARCH64"
EDK2_PLATFORM_DSC:qemuarm64-secureboot  = "ArmVirtPkg/ArmVirtQemu.dsc"
EDK2_BIN_NAME:qemuarm64-secureboot      = "QEMU_EFI.fd"
EDK2_BUILD_RELEASE:qemuarm64-secureboot = "0"
EDK2_EXTRA_BUILD:qemuarm64-secureboot += " -D SECURE_BOOT_ENABLE=TRUE"
EDK2_EXTRA_BUILD:qemuarm64-secureboot += " -D NETWORK_PXE_BOOT_ENABLE=FALSE"

do_install:append:qemuarm64-secureboot() {
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/${EDK2_BIN_NAME} ${D}/firmware/
}

COMPATIBLE_MACHINE:qemuarm-secureboot = "qemuarm-secureboot"
EDK2_PLATFORM:qemuarm-secureboot      = "ArmVirtQemu-ARM"
EDK2_PLATFORM_DSC:qemuarm-secureboot  = "ArmVirtPkg/ArmVirtQemu.dsc"
EDK2_BIN_NAME:qemuarm-secureboot      = "QEMU_EFI.fd"
EDK2_BUILD_RELEASE:qemuarm-secureboot = "0"
EDK2_EXTRA_BUILD:qemuarm-secureboot += " -D SECURE_BOOT_ENABLE=TRUE"
EDK2_EXTRA_BUILD:qemuarm-secureboot += " -D NETWORK_PXE_BOOT_ENABLE=FALSE"

do_install:append:qemuarm-secureboot() {
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/${EDK2_BIN_NAME} ${D}/firmware/
}

COMPATIBLE_MACHINE:qemuarm64 = "qemuarm64"
EDK2_PLATFORM:qemuarm64      = "ArmVirtQemu-AARCH64"
EDK2_PLATFORM_DSC:qemuarm64  = "ArmVirtPkg/ArmVirtQemu.dsc"
EDK2_BIN_NAME:qemuarm64      = "QEMU_EFI.fd"
EDK2_EXTRA_BUILD:qemuarm64 += " -D NETWORK_PXE_BOOT_ENABLE=FALSE"
EDK2_BUILD_RELEASE:qemuarm64 = "0"

do_install:append:qemuarm64() {
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/${EDK2_BIN_NAME} ${D}/firmware/
}

COMPATIBLE_MACHINE:qemuarm = "qemuarm"
EDK2_PLATFORM:qemuarm      = "ArmVirtQemu-ARM"
EDK2_PLATFORM_DSC:qemuarm  = "ArmVirtPkg/ArmVirtQemu.dsc"
EDK2_BIN_NAME:qemuarm      = "QEMU_EFI.fd"
EDK2_EXTRA_BUILD:qemuarm += " -D NETWORK_PXE_BOOT_ENABLE=FALSE"
EDK2_BUILD_RELEASE:qemuarm = "0"

do_install:append:qemuarm() {
    install ${B}/Build/${EDK2_PLATFORM}/${EDK2_BUILD_MODE}_${EDK_COMPILER}/FV/${EDK2_BIN_NAME} ${D}/firmware/
}
