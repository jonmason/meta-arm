# TC specific configuration

COMPATIBLE_MACHINE = "(tc?)"
HAFNIUM_PLATFORM = "secure_tc"

# Intermediate SHA with 2.7 baseline version
SRCREV = "dd0561820946fe23bcd57cc129140437f72102a5"
PV = "2.7+git${SRCPV}"

FILESEXTRAPATHS:prepend:tc := "${THISDIR}/files/tc:"

SRC_URI:remove = " \
    file://host-ld.patch \
    file://native-dtc.patch"

SRC_URI:append = " \
        file://0001-feat-emulate-cntp-timer-register-accesses-using-cnth.patch \
        file://0002-feat-emulate-interrupt-controller-register-access.patch \
        file://0003-tc-increase-heap-pages.patch \
        "

do_compile() {
    PATH="${S}/prebuilts/linux-x64/clang/bin:$PATH" oe_runmake -C ${S}
}
