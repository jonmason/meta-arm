SUMMARY = "Clang Indexing Library Bindings"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=ff42885ed2ab98f1ecb8c1fc41205343"
HOMEPAGE = "https://github.com/llvm/llvm-project/tree/main/clang/bindings/python"

inherit pypi setuptools3

SRC_URI[sha256sum] = "a1214966d08d73d971287fc3ead8dfaf82eb07fb197680d8b3859dbbbbf78250"

BBCLASSEXTEND = "native nativesdk"
