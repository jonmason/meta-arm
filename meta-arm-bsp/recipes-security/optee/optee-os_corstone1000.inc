require optee-os_corstone1000_common.inc

DEPENDS += " secure-partitions"
EXTRA_OEMAKE +="'SP_PACKAGING_METHOD=embedded'"

TS_INSTALL_PREFIX_PATH="${RECIPE_SYSROOT}/firmware/sp/opteesp"
EXTRA_OEMAKE += "'TS_INSTALL_PREFIX=${TS_INSTALL_PREFIX_PATH}'"

# se-proxy secure partition
SP_MKFILE_PATH="${TS_INSTALL_PREFIX}/lib/make/se-proxy.mk"

EXTRA_OEMAKE += "'CFG_SP_MKFILE_PATH=${SP_MKFILE_PATH}'"
EXTRA_OEMAKE += "'CFG_EMBED_DTB_SOURCE_FILE=${TS_INSTALL_PREFIX_PATH}/manifest/46bb39d1-b4d9-45b5-88ff-040027dab249.dts'"
