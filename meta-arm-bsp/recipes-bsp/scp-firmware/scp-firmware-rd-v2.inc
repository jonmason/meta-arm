# Neoverse V2 specific SCP configurations and build instructions

COMPATIBLE_MACHINE:rd-v2 = "rd-v2"
SCP_PLATFORM = "rdn2"
EXTRA_OECMAKE:append = " \
    -DSCP_PLATFORM_VARIANT=0 \
"

FW_TARGETS = "scp"
