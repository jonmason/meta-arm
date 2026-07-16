# RD N2 specific TFA support

COMPATIBLE_MACHINE = "rdn2"
TFA_PLATFORM       = "rdn2"
TFA_BUILD_TARGET   = "all fip"
TFA_INSTALL_TARGET = "bl1 fip"
TFA_DEBUG          = "1"
TFA_MBEDTLS        = "1"
TFA_UBOOT          = "0"
TFA_UEFI           = "1"

EXTRA_OEMAKE += "TRUSTED_BOARD_BOOT=1 GENERATE_COT=1 ARM_ROTPK_LOCATION=devel_rsa \
                     ROT_KEY=plat/arm/board/common/rotpk/arm_rotprivk_rsa.pem"

# If GENERATE_COT is set, then tf-a will try to use local poetry install
# to run the python cot-dt2c command.  Disable the local poetry and use
# the provided cot-dt2c.
EXTRA_OEMAKE += "POETRY=''"
DEPENDS += "cot-dt2c-native"

SRC_URI_TRUSTED_FIRMWARE_A = "git://gitlab.arm.com/infra-solutions/reference-design/platsw/trusted-firmware-a.git;protocol=https"
SRCBRANCH = "refinfra"
# Use common ancestor of RD-INFRA-2025.07.03 and lts-v2.14.0
SRCREV_tfa = "d154fe2bf0616f2e78965207c32b6e83ba12292e"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"
SRC_URI += "\
    file://0001-TEMP-mbedtls-version-change-for-build.patch \
    file://0002-fix-neoverse-rd-fix-UART-console-init-regression.patch \
    file://0003-TEMP-fix-bl31-init-GIC-before-platform-setup.patch \
    file://0004-feat-neoverse-rd-Add-support-build-multiple-platform.patch \
    file://0005-feat-delegated_attestation-introduce-generic-driver.patch \
    file://0006-fix-drivers-arm-rse-force-rse-comms-embed-in-RME.patch \
    file://0007-spm-enable-sve-for-non-secure-and-secure-world.patch \
    file://0008-feat-plat-arm-rdfremont-Add-a-new-property-for-PCIe-.patch \
    file://0009-feat-plat-arm-sgi-Enable-support-to-read-pcie-data-f.patch \
    file://0010-feat-plat-arm-rdn2-Add-a-new-property-for-PCIe-in-FD.patch \
    file://0011-feat-rdfremont-initialize-SMMUv3-on-rdfremont-varian.patch \
    file://0012-feat-rdfremont-enable-gpc-checks-on-remote-gpc_smmu-.patch \
    file://0013-HACK-spinlock-send-explicit-event-after-store-releas.patch \
    file://0014-neoverse-rd-add-sds-banks-for-the-remote-chips.patch \
    file://0015-feat-neoverse-rd-Enable-CTX_INCLUDE_SVE_REGS.patch \
    file://0016-refactor-ras-save-and-restore-el1-context-if-SPMD_SP.patch \
    file://0017-refactor-sdei-save-and-restore-el1-context-if-SPMD_S.patch \
    file://0018-feat-neoverse_rd-firmware-first-error-handling-suppo.patch \
    file://0019-feat-neoverse_rd-enable-shared-RAM-error-handling-su.patch \
    file://0020-feat-neoverse_rd-use-spmd-interface-to-forward-inter.patch \
    file://0021-feat-spmd-add-support-to-delegate-interrupt-to-sp.patch \
    file://0022-feat-rdfremont-firmware-first-error-handling-support.patch \
    file://0023-feat-rdfremont-enable-Shared-RAM-RAS-support-on-RD-F.patch \
    file://0024-feat-rdfremont-enable-Poseidon-CPU-error-handling-su.patch \
    file://0025-feat-neoversr_rd-carve-out-region-for-cper-buffer.patch \
    file://0026-feat-neoverse_rd-add-dts-entry-for-cper-buffer.patch \
    file://0027-TEMP-EINJ-feat-neoverse_rd-carve-out-region-for-einj.patch \
    file://0028-TEMP-EINJ-feat-neoverse_rd-update-einj-buffer-to-ena.patch \
    file://0029-feat-neoverse_rd-adds-mapping-in-SRAM-Region-for-RAS.patch \
    file://0030-feat-neoverse-introduce-build-option-for-platform-er.patch \
    file://0031-feat-neoverse_rd-add-platform-firmware-error-injecti.patch \
    file://0032-feat-neoverse_rd-add-memory-mmap-and-tzc-entry-for-E.patch \
    file://0033-feat-rdn2-add-base-ram-error-injection-support.patch \
    file://0034-feat-rdfremont-add-base-ram-error-injection-support.patch \
    file://0035-feat-ras-add-CPU-error-injection-support.patch \
    file://0036-feat-neoverse_rd-adds-CPU-error-injection-support.patch \
    file://0037-feat-rdn2-enable-CPU-error-injection-on-RD-N2-Cfg1.patch \
    file://0038-feat-rdfremont-enable-cpu-error-injectio-on-RD-Fremo.patch \
    file://0039-feat-neoverse-rd-enable-logical-partition-support-in.patch \
    file://0040-feat-rdn2-Update-build-flags-to-enable-RAS-kernel-fi.patch \
    file://0041-feat-ras-add-support-for-OEM-error-injection-support.patch \
    file://0042-TEMP-feat-rdfremont-Guards-around-NRD_PAS_CPER-to-fi.patch \
    file://0043-feat-ras-rdfremont-Update-error-injection-buffer-add.patch \
    file://0044-spm-move-non-secure-buffer-out-of-secure-carveout.patch \
    file://0045-feat-neoverse-rd-add-firmware-definitions-for-fourth.patch \
    file://0046-feat-neoverse-rd-Add-support-plarform-RD-V3-R1.patch \
    file://0047-feat-neoverse-rd-Add-support-plarform-RD-V3-R1-Cfg1.patch \
    file://0048-feat-neoverse-rd-set-interrupt-priority-for-reboot-i.patch \
    file://0049-feat-neoverse-rd-enable-graceful-reset-support-for-R.patch \
    file://0050-feat-ras-Modify-ERXMISC0-register-to-be-read-writebl.patch \
    file://0051-feat-ras-Add-support-for-FFH-CPU-CE-error-injection.patch \
    file://0052-feat-rdv3r1-set-CTX_INCLUDE_SVE_REGS-build-flag-for-.patch \
    file://0053-TEMP-EINJ-CMN-feat-einj-Extends-ARM-SIP-for-Platform.patch \
    file://0054-TEMP-EINJ-CMN-feat-einj-EINJ-test-code-for-CMN-KFH.patch \
    file://0055-fix-neoverse_rd-remove-redundant-NRD_DRAM1_CARVEOUT_.patch \
    file://0056-feat-nrd4-update-dram-block2-base-address.patch \
    file://0057-fix-rdv3r1-add-console-name-to-checksum-calculation-.patch \
    file://0058-fix-rdv3r1-update-multichip-data-format.patch \
    file://0059-fix-MPMM-enable-CPUMPMMCR_EL3-control-register.patch \
    file://0060-feat-neoverse-enable-mpmm-in-neoverse_v3-core.patch \
    file://0061-feat-rdv3-Enable-MPMM-in-RDV3-platform-variant.patch \
    file://0062-Revert-chore-fix-preprocessor-checks.patch \
    file://0063-Revert-refactor-convert-arm-platforms-to-use-the-gen.patch \
    file://0064-Revert-refactor-gic-promote-most-of-the-GIC-driver-t.patch \
    file://0065-Revert-refactor-make-arm_gicv2.c-and-arm_gicv3.c-com.patch \
    file://0066-Revert-refactor-fvp-use-more-arm-generic-code-for-gi.patch \
    file://0067-feat-rdv3-increase-BL31-size.patch \
    file://0068-fix-rdv3cfg1-Bumping-up-BL31-stack-size-to-0x700.patch \
    file://0069-fix-rdv3r1-update-with-upstream-changes.patch \
    file://0070-fix-rdv3r1-update-PLAT_MHU-flag.patch \
    "

# FIXME - hacking around using the 2.14 based recipe
SRC_URI:remove = "file://0001-feat-build-add-HOSTLDFLAGS-to-pass-flags-to-host-lin.patch"
LIC_FILES_CHKSUM:remove = "file://docs/license.rst;md5=6ed7bace7b0bc63021c6eba7b524039e"
LIC_FILES_CHKSUM += "file://docs/license.rst;md5=1118e32884721c0be33267bd7ae11130"

# sub-directory in which mbedtls will be downloaded
# Only needed for legacy versions, as v2.15.0 added this as a git submodule
TFA_MBEDTLS_DIR ?= "mbedtls"
# This should be set to MBEDTLS download URL if MBEDTLS is needed
SRC_URI_MBEDTLS ??= ""
# This should be set to MBEDTLS LIC FILES checksum
LIC_FILES_CHKSUM_MBEDTLS ??= ""
# add MBEDTLS to our sources if activated
SRC_URI:append = " ${@bb.utils.contains('TFA_MBEDTLS', '1', '${SRC_URI_MBEDTLS}', '', d)}"
# Update license variables
LICENSE:append = "${@bb.utils.contains('TFA_MBEDTLS', '1', ' AND Apache-2.0', '', d)}"
LIC_FILES_CHKSUM:append = "${@bb.utils.contains('TFA_MBEDTLS', '1', ' ${LIC_FILES_CHKSUM_MBEDTLS}', '', d)}"
# add mbed TLS to version
SRCREV_FORMAT:append = "${@bb.utils.contains('TFA_MBEDTLS', '1', '_mbedtls', '', d)}"

# Handle MBEDTLS
EXTRA_OEMAKE += "${@bb.utils.contains('TFA_MBEDTLS', '1', 'MBEDTLS_DIR=${TFA_MBEDTLS_DIR}', '', d)}"

# in TF-A src, docs/getting_started/prerequisites.rst lists the expected version mbedtls
# mbedtls-3.6.5
SRCBRANCH_MBEDTLS = "mbedtls-3.6"
SRC_URI_MBEDTLS = "gitsm://github.com/Mbed-TLS/mbedtls;name=mbedtls;protocol=https;destsuffix=${BB_GIT_DEFAULT_DESTSUFFIX}/mbedtls;branch=${SRCBRANCH_MBEDTLS}"
SRCREV_mbedtls = "e185d7fd85499c8ce5ca2a54f5cf8fe7dbe3f8df"

LIC_FILES_CHKSUM_MBEDTLS = "file://mbedtls/LICENSE;md5=379d5819937a6c2f1ef1630d341e026d"
