# FVP base specific U-boot support

SRC_URI:append = " file://bootargs.cfg \
    file://0001-Revert-vexpress64-pick-DRAM-size-from-DT.patch \
    "
