SRC_URI_RMM	     ?= "gitsm://git.trustedfirmware.org/TF-RMM/tf-rmm.git;protocol=https"
SRCREV_rmm	     ?= "01a3cb75c6e6c50851d5d939d237966d110ed91d"
SRCBRANCH_rmm	     ?= "main"

require recipes-bsp/rmm/rmm.inc
