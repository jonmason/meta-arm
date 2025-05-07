SUMMARY = "Flattened Device Tree Python Module"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"
HOMEPAGE = "https://github.com/molejar/pyFDT"

inherit pypi setuptools3

SRC_URI[sha256sum] = "81a215930fef2ab8894913c4f474105bb53e14f07129fe07cb6eff2d5fdf26d2"

BBCLASSEXTEND = "native nativesdk"
