require recipes-bsp/trusted-firmware-a/fiptool-native_2.15.0.bb

SUMMARY = "TC3 platform fiptool"
S = "${UNPACKDIR}/fiptool-${PV}"
EXTRA_OEMAKE:append = " PLAT=tc TARGET_PLATFORM=3"
