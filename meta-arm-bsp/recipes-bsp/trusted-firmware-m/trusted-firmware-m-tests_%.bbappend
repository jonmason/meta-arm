# The FVP regression builds need the same Ethos-U source as TF-M.
MACHINE_TFM_TESTS_REQUIRE ?= ""
MACHINE_TFM_TESTS_REQUIRE:corstone300-fvp = "trusted-firmware-m-ethos.inc"

require ${MACHINE_TFM_TESTS_REQUIRE}
