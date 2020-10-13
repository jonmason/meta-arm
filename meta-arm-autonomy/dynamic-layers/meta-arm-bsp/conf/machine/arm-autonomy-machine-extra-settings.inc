# Require extra machine specific settings
ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE ?= ""
ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE_n1sdp = "n1sdp-extra-settings.inc"
ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE_fvp-base = "fvp-base-extra-settings.inc"
ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE_juno = "juno-extra-settings.inc"

require ${ARM_BSP_DYN_MACHINE_EXTRA_REQUIRE}
