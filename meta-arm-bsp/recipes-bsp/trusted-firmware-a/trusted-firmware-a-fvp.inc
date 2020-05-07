# FVP specific TFA parameters

#
# Armv8-A Base Platform FVP and Armv8-A Foundation Platform uses the same
# TFAs.
#

COMPATIBLE_MACHINE = "fvp-base|foundation-armv8"
TFA_PLATFORM = "fvp"
TFA_DEBUG = "1"
TFA_MBEDTLS = "1"
TFA_UBOOT = "1"
TFA_BUILD_TARGET = "bl1 bl2 bl31 dtbs fip"
