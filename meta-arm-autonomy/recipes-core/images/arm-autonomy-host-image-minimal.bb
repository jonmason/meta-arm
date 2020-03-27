# Recipe to create a minimal Arm Autonomy stack host image

DESCRIPTION = "Arm Autonomy stack host minimal image"

inherit core-image

LICENSE = "MIT"

# Includes minimal set required to start and manage guest. The xen specific
# modules are not explicitly included as they are built as part of the kernel
# image for performance reasons. Includes all kernel modules anyway as it makes
# life easier and does not cost that much in size.
IMAGE_INSTALL += " \
    packagegroup-core-boot \
    packagegroup-core-ssh-openssh \
    kernel-modules \
    xen-base \
    qemu \
    "

python __anonymous() {
    if bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', False, True, d):
        raise bb.parse.SkipRecipe("DISTRO_FEATURES does not contain 'arm-autonomy-host'")

    if bb.utils.contains('DISTRO_FEATURES', 'xen', False, True, d):
        raise bb.parse.SkipRecipe("DISTRO_FEATURES does not contain 'xen'")
}
