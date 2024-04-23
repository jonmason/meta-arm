FILESEXTRAPATHS:prepend:corstone1000 := "${THISDIR}/corstone1000:"

COMPATIBLE_MACHINE:corstone1000 = "corstone1000"
SRC_URI:append:corstone1000  = " \
    file://0001-Add-stub-capsule-update-service-components.patch \
    file://0002-Fixes-in-AEAD-for-psa-arch-test-54-and-58.patch \
    file://0003-FMP-Support-in-Corstone1000.patch \
    file://0004-GetNextVariableName-Fix.patch     \
    file://0005-plat-corstone1000-add-compile-definitions-for-ECP_DP.patch \
    file://0006-plat-corstone1000-Use-the-stateless-platform-service.patch \
    file://0007-plat-corstone1000-Initialize-capsule-update-provider.patch \
    file://0008-platform-corstone1000-fix-synchronization-issue.patch \
    file://0009-plat-corstone1000-fmp-client-id.patch \
    file://0010-Decrease-SMM_GATEWAY_MAX_UEFI_VARIABLES.patch \
    file://0011-Fix-psa_ipc-service-s-psa_call.patch \
    file://0012-Make-RPC-caller-session-SHM-size-build-time-configur.patch \
    file://0013-Set-RPC-caller-session-SHM-size-for-Corstone-1000-SM.patch \
    file://0014-Use-__packed-for-the-variable_metadata-struct.patch \
    "


COMPATIBLE_MACHINE:n1sdp = "n1sdp"

COMPATIBLE_MACHINE:fvp-base = "fvp-base"
TS_PLATFORM:fvp-base = "arm/fvp/fvp_base_revc-2xaemv8a"
