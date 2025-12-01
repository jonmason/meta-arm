require fvp-envelope.inc

LICENSE:append = " & Artistic-2.0 & BSL-1.0 & BSD-2-Clause & Unlicense"

SUMMARY = "Arm Fixed Virtual Platform - Armv-A Base RevC Architecture Envelope Model FVP"
LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses/third_party_licenses.txt;md5=a5ce56e117d0ab63791fbb7c35ec2211 \
                    file://license_terms/third_party_licenses/arm_license_management_utilities/third_party_licenses.txt;md5=25c38921c5071644ed088288e5bd9b8e"

SRC_URI[fvp-aarch64.sha256sum] = "6b72a16f12ef619faeb9f441350c04b6c12687693061a4d2621e942cfaec5eab"
SRC_URI[fvp-x86_64.sha256sum] = "59d8d74dc9580e64a77c73fb571bdd3c0f583407dd6442de4c886086b8513df9"

# The CSS used in the FVP homepage make it too difficult to query with the tooling currently in Yocto
UPSTREAM_VERSION_UNKNOWN = "1"

MODEL_CODE = "FVP_Base_RevC-2xAEMvA"

COMPATIBLE_HOST = "(aarch64|x86_64).*-linux"
