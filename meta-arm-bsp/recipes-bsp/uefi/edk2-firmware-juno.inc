EDK2_PLATFORM      = "ArmJuno"
EDK2_PLATFORM_DSC  = "Platform/ARM/JunoPkg/ArmJuno.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"

COMPATIBLE_MACHINE = "juno"

# As of 2022-01-10 the Juno build fails with Clang:
# edk2-firmware/202111-r0/edk2/edk2-platforms/Platform/ARM/Library/ArmShellCmdRunAxf/RunAxf.c:216:11:
# error: variable 'FileSize' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]
TOOLCHAIN = "gcc"
