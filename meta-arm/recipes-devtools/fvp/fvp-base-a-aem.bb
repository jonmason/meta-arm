require fvp-envelope.inc

SUMMARY = "Arm Fixed Virtual Platform - Armv-A Base RevC Architecture Envelope Model FVP"
LIC_FILES_CHKSUM = "file://license_terms/license_agreement.txt;md5=1a33828e132ba71861c11688dbb0bd16 \
                    file://license_terms/third_party_licenses.txt;md5=3db0c4947b7e3405c40b943672d8de2f"

PV = "11.15.18"

SRC_URI = "https://developer.arm.com/-/media/Files/downloads/ecosystem-models/${MODEL_CODE}_${PV_URL}.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "05e474d6b8197c749c66968315fdb7059d398b279bef59787025a88219c71ae4"

MODEL_CODE = "FVP_Base_RevC-2xAEMvA"
