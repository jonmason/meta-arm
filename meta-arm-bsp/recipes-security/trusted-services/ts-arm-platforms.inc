FILESEXTRAPATHS:prepend:corstone1000 := "${THISDIR}/corstone1000:"

COMPATIBLE_MACHINE:corstone1000 = "corstone1000"
SRC_URI:append:corstone1000  = " \
    file://0001-Fix-in-AEAD-for-psa-arch-test-254.patch \
    file://0002-Fix-psa-api-crypto-test-no-243.patch \
    file://0003-Remove-Werror-flag.patch \
    file://0004-Remove-PLATFORM_HAS_ATTEST_PK-define-from-IAT-test.patch \
    file://0005-Make-RSS-and-MHU-sizes-compile-time-definitions-user.patch \
    file://0006-Align-PSA-Crypto-with-TF-Mv2.1.patch \
    file://0007-Revert-Load-and-store-UEFI-variable-index-in-chunks.patch \
    file://0008-se-proxy-protobuf-change.patch \
    file://0009-Platform-Corstone1000-Add-PLATFORM_IS_FVP-toggle-for.patch \
    file://0010-Integrate-PSA-FWU-IPC-framework-for-Corstone-1000.patch \
    file://0011-Load-initial-image-state-in-PSA-FWU-M-update-agent.patch \
    file://0012-Corstone1000-Define-PSA-FWU-image-mapping-structure.patch \
    file://0013-Fix-PSA-FWU-IPC-psa_fwu_install-return-value-check.patch \
    file://0014-fwu-Add-EFI-ESRT-v1-support.patch \
    file://0015-platform-corstone1000-Enable-ESRT-support.patch \
    file://0016-platform-corstone1000-Add-event-provider-proxy.patch \
    file://0017-platform-corstone1000-Define-GUID-for-each-payloads.patch \
    file://0018-Add-the-com-buffer-address-and-page-count.patch \
    file://0021-Align-PSA-Crypto-structs-with-TF-Mv2.1.1.patch \
    "
# The patches above introduce errors with GCC 14.1, silence them for now
CFLAGS:append:corstone1000 = " -Wno-int-conversion -Wno-implicit-function-declaration"

COMPATIBLE_MACHINE:fvp-base = "fvp-base"
TS_PLATFORM:fvp-base = "arm/fvp/fvp_base_revc-2xaemv8a"
