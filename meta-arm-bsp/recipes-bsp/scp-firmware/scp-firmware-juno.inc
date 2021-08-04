# juno specific SCP configuration

COMPATIBLE_MACHINE = "juno"

SCP_PLATFORM = "juno"
FW_TARGETS = "scp"
FW_INSTALL:append = " romfw_bypass"
