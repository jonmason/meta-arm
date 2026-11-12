# OE-Core's pinned v2026.07 revision is on master, not the current main branch.
SRC_URI:remove:class-native = "git://git.u-boot-project.org/u-boot/u-boot.git;protocol=https;branch=main;tag=v${PV}"
SRC_URI:append:class-native = " git://git.u-boot-project.org/u-boot/u-boot.git;protocol=https;nobranch=1;tag=v${PV}"
