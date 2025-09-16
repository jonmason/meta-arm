FILESEXTRAPATHS:prepend:corstone1000 := "${THISDIR}/corstone1000:"

COMPATIBLE_MACHINE:corstone1000 = "corstone1000"
SRC_URI:append:corstone1000  = " \
    file://0001-platform-corstone1000-Add-CORSTONE_1000_TYPE-variabl.patch \
    file://0002-platform-corstone1000-Add-event-provider-proxy-for-b.patch \
    file://0003-fwu-se-proxy-Allow-platform-override-of-FWU-mapping-.patch \
    file://0004-fwu-Coerce-PSA_SUCCESS_REBOOT-and-PSA_SUCCESS_RESTAR.patch \
    file://0005-platform-corstone1000-Add-MM-communication-buffer-co.patch \
    file://0006-fwu-Add-support-for-ESRT-v1-in-PSA-FWU-M-agent.patch \
    file://0007-Make-treating-warnings-as-errors-configurable.patch \
    file://0008-smm-gateway-config-Remove-Werror-compile-option.patch \
    file://0009-fwu-proxy-refactor-image-mapping.patch \
    file://0010-Revert-Load-and-store-UEFI-variable-index-in-chunks.patch \
    file://0011-Remove-PLATFORM_HAS_ATTEST_PK-define-from-IAT-test.patch \
    file://0012-psa-crypto-fix-AEAD-block-cypher-support.patch \
"
# The patches above introduce errors with GCC 14.1, silence them for now
CFLAGS:append:corstone1000 = " -Wno-int-conversion -Wno-implicit-function-declaration"

COMPATIBLE_MACHINE:fvp-base = "fvp-base"
TS_PLATFORM:fvp-base = "arm/fvp/fvp_base_revc-2xaemv8a"

EXTRA_OECMAKE:append:corstone1000 = " \
    -DCORSTONE_1000_TYPE=${CORSTONE_1000_TYPE} \
    -DCMAKE_COMPILE_WARNING_AS_ERROR=OFF \
"
