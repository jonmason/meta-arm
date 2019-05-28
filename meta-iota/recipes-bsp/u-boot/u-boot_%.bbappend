SRCREV = "9bed08a2ed8d4915e694e5b4a030bd361b829a52"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=a2c678cfd4a4d97135585cad908541c6"

SRC_URI_vexpress-a5 += "\
  git://git.linaro.org/landing-teams/working/arm/u-boot;protocol=https;nobranch=1 \
  file://0001-vexpress64-setup-kernel-and-rootfs-from-flash-for-fvpve.patch \
  file://0001-tools-allow-to-override-python.patch \
  "

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

PLATFORM_vexpress-a5 = "fvp_ve"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

COMPATIBLE_MACHINE = "(vexpress-a5)"

do_compile_vexpress-a5() {
    mkdir -p ${B}

    oe_runmake -C ${S} BUILD_BASE=${B} \
      BUILD_PLAT=${B}/${PLATFORM}/ \
      vexpress_aemv8a_aarch32_defconfig \
      O=${B}

    oe_runmake -C ${S} BUILD_BASE=${B} \
      BUILD_PLAT=${B}/${PLATFORM}/ \
      SUPPORT_ARCH_TIMER=no \
      O=${B}
}
