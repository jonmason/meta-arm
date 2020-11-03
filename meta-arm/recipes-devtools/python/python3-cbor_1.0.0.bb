DESCRIPTION = "An implementation of RFC 7049 - Concise Binary Object Representation (CBOR)."
HOMEPAGE = "https://github.com/brianolson/cbor_py"

LICENSE = "Apache-2.0"
# Use a line from setup.py until LICENSE is distributed
# (https://github.com/brianolson/cbor_py/issues/20)
LIC_FILES_CHKSUM = "file://setup.py;beginline=88;endline=88;md5=267392b618a88b03e5987f69d9b98699"

SRC_URI[md5sum] = "22b03b59784fd78cb6c27aa498af0db6"
SRC_URI[sha256sum] = "13225a262ddf5615cbd9fd55a76a0d53069d18b07d2e9f19c39e6acb8609bbb6"

PYPI_PACKAGE = "cbor"

inherit pypi setuptools3

BBCLASSEXTEND = "native"
