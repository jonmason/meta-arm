COMPATIBLE_MACHINE = "fvp-baser-aemv8r64"

FILESEXTRAPATHS_prepend := "${THISDIR}/files/${MACHINE}:"
SRC_URI_append = " \
    file://0001-Decouple-V2M_SYS-config-by-auto-detect-dtb-node.patch \
    file://0002-arch64-Introduce-EL2-boot-code-for-v8-r64.patch \
    "

BOOT_WRAPPER_AARCH64_CMDLINE = "\
earlycon console=ttyAMA0 loglevel=8 rootfstype=ext4 root=/dev/vda1 rw"

EXTRA_OECONF_remove = "--enable-psci"

TUNE_CCARGS = ""
