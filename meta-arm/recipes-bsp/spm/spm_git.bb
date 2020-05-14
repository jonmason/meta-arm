# TF-A spm
#

# Never select this if another version is available
DEFAULT_PREFERENCE = "-1"

require spm.inc

SRC_URI = "gitsm://git.trustedfirmware.org/hafnium/hafnium.git;;protocol=https;name=spm"
SRCREV_FORMAT = "spm"

S = "${WORKDIR}/git"
