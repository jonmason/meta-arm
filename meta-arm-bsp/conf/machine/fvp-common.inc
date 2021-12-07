# FVP common parameters

#
# Capturing FVP common configurations (Armv8-A Base Platform FVP,
# Armv8-A Foundation Platform and Armv7-A Base Platform FVP).
#

MACHINE_FEATURES = "optee"

IMAGE_FSTYPES += "wic"
WKS_FILE ?= "fvp-base.wks"

SERIAL_CONSOLES = "115200;ttyAMA0"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-yocto"

PREFERRED_VERSION_u-boot ?= "2021.10"

EXTRA_IMAGEDEPENDS += "trusted-firmware-a u-boot"

# As this is a virtual target that will not be used in the real world there is
# no need for real SSH keys.  Disable rng-tools (which takes too long to
# initialise) and install the pre-generated keys.
PACKAGECONFIG:remove:pn-openssh = "rng-tools"
MACHINE_EXTRA_RRECOMMENDS += "ssh-pregen-hostkeys"

TEST_TARGET = "OEFVPTarget"
