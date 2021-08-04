COMPATIBLE_MACHINE = "fvp-baser-aemv8r64"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/${MACHINE}:"
SRC_URI:append = " \
    file://0001-Decouple-V2M_SYS-config-by-auto-detect-dtb-node.patch \
    file://0002-arch64-Introduce-EL2-boot-code-for-v8-r64.patch \
    file://0003-Allow-enable-psci-to-choose-between-smc-and-hvc.patch \
    "

BOOT_WRAPPER_AARCH64_CMDLINE = "\
earlycon console=ttyAMA0 loglevel=8 rootfstype=ext4 root=/dev/vda1 rw"

EXTRA_OECONF += "--enable-psci=hvc"

TUNE_CCARGS = ""
