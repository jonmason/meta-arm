COMPATIBLE_MACHINE = "tc3"

# OE-Core's pinned v2026.07 revision is on master, not the current main branch.
SRC_URI:remove:tc3 = "git://git.u-boot-project.org/u-boot/u-boot.git;protocol=https;branch=main;tag=v${PV}"
SRC_URI:append:tc3 = " git://git.u-boot-project.org/u-boot/u-boot.git;protocol=https;nobranch=1;tag=v${PV}"
SRC_URI:remove:class-devupstream:tc3 = "git://git.u-boot-project.org/u-boot/u-boot.git;protocol=https;nobranch=1;tag=v${PV}"
