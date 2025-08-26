require recipes-security/optee/optee-client.inc

# v4.7.0
SRCREV = "23c112a6f05cc5e39bd4aaf52ad515cad532237d"
SRC_URI += "file://0001-tee-supplicant-update-udev-systemd-install-code.patch"

inherit pkgconfig
DEPENDS += "util-linux"
EXTRA_OEMAKE += "PKG_CONFIG=pkg-config"
