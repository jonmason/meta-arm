# Only enable linux-yocto-rt for n1sdp
LINUX_YOCTO_RT_REQUIRE ?= ""
LINUX_YOCTO_RT_REQUIRE_n1sdp = "linux-arm-platforms.inc"

require ${LINUX_YOCTO_RT_REQUIRE}
