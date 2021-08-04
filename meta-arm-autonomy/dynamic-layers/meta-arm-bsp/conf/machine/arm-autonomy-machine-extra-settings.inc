# Require extra machine specific settings
ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE ?= ""
ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE:n1sdp = "n1sdp-extra-settings.inc"
ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE:fvp-base = "fvp-base-extra-settings.inc"
ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE:juno = "juno-extra-settings.inc"

require ${ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE}
