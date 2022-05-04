# TC specific configuration

COMPATIBLE_MACHINE = "(tc?)"
HAFNIUM_PLATFORM = "secure_tc"

SRCREV = "4eb7b54348234d7f4bbac64bac28f683d6574ba9"
FILESEXTRAPATHS:prepend:tc := "${THISDIR}/files/tc:"

SRC_URI:remove = " \
    file://host-ld.patch \
    file://native-dtc.patch"

do_compile() {
    PATH="${S}/prebuilts/linux-x64/clang/bin:$PATH" oe_runmake -C ${S}
}
