FILESEXTRAPATHS:prepend:corstone1000 := "${THISDIR}/corstone1000:"

COMPATIBLE_MACHINE:corstone1000 = "corstone1000"
SRC_URI:append:corstone1000  = " \
    file://0009-platform-corstone1000-Add-CORSTONE_1000_TYPE-variabl.patch \
    file://0016-platform-corstone1000-Add-event-provider-proxy.patch \
    file://0017-platform-corstone1000-Define-GUID-for-each-payloads.patch \
    file://0013-Fix-PSA-FWU-IPC-psa_fwu_install-return-value-check.patch \
    file://0018-Add-the-com-buffer-address-and-page-count.patch \
    file://0014-fwu-Add-EFI-ESRT-v1-support.patch \
    file://0022-Make-treating-warnings-as-errors-configurable.patch \
    file://0003-Remove-Werror-flag.patch \
    file://0007-fwu-proxy-refactor-image-mapping.patch \
    file://0007-Revert-Load-and-store-UEFI-variable-index-in-chunks.patch \
    file://0004-Remove-PLATFORM_HAS_ATTEST_PK-define-from-IAT-test.patch \
    file://0024-psa-crypto-fix-AEAD-block-cypher-support.patch \
"
# The patches above introduce errors with GCC 14.1, silence them for now
CFLAGS:append:corstone1000 = " -Wno-int-conversion -Wno-implicit-function-declaration"

COMPATIBLE_MACHINE:fvp-base = "fvp-base"
TS_PLATFORM:fvp-base = "arm/fvp/fvp_base_revc-2xaemv8a"

EXTRA_OECMAKE:append:corstone1000 = " \
    -DCORSTONE_1000_TYPE=${CORSTONE_1000_TYPE} \
    -DCMAKE_COMPILE_WARNING_AS_ERROR=OFF \
"
