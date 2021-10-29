SUMMARY = "MCUboot's image signing and key management"
LICENSE = "Apache-2.0"
AUTHOR = "The MCUboot committers <mcuboot@groups.io>, \
          Abdellatif El Khlifi <abdellatif.elkhlifi@arm.com>"

LIC_FILES_CHKSUM = "file://PKG-INFO;md5=e32b214fd9c204b77a99a97aa903757b"

SRC_URI[md5sum] = "de0005dc13ce9e5e6aecdedfd0956286"

DEPENDS:corstone1000 = "python3-cryptography python3-intelhex python3-click python3-cbor"

inherit pypi setuptools3

BBCLASSEXTEND = "native nativesdk"
