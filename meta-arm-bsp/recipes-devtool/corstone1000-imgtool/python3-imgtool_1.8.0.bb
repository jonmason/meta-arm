SUMMARY = "MCUboot's image signing and key management"
LICENSE = "Apache-2.0"
AUTHOR = "The MCUboot committers <mcuboot@groups.io>, \
          Abdellatif El Khlifi <abdellatif.elkhlifi@arm.com>"

LIC_FILES_CHKSUM = "file://setup.py;md5=bd908c2a1211013db5df04f0ec181b9b"

SRC_URI[md5sum] = "a515e40ae31c1d7a70e653b997bb112b"

RDEPENDS_${PN} = "python3-cryptography-native python3-intelhex-native python3-click-native python3-cbor-native"

inherit pypi setuptools3

BBCLASSEXTEND = "native nativesdk"
