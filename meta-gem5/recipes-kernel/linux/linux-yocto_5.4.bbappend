FILESEXTRAPATHS_prepend := "${THISDIR}:${THISDIR}/files:"

COMPATIBLE_MACHINE_gem5-arm64 = "gem5-arm64"
KMACHINE_gem5-arm64 = "gem5-arm64"
SRC_URI_append_gem5-arm64 = " file://gem5-kmeta;type=kmeta;name=gem5-kmeta;destsuffix=gem5-kmeta \
                              file://dts/gem5-arm64;subdir=add-files"

do_patch_append_gem5-arm64() {
    tar -C ${WORKDIR}/add-files/dts -cf - gem5-arm64 | \
        tar -C arch/arm64/boot/dts -xf -
}
