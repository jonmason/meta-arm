# Recipe to create a minimal Arm Autonomy reference stack host image

DESCRIPTION = "Arm Autonomy stack host minimal image"

# When alternate-kernel DISTRO_FEATURE is present we will build
# and install the alternate kernel
inherit ${@bb.utils.filter('DISTRO_FEATURES', 'alternate-kernel', d)}

inherit core-image features_check

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Includes minimal set required to start and manage guest. The xen specific
# modules are not explicitly included as they are built as part of the kernel
# image for performance reasons. It doesn't include all kernel modules to
# reduce the image size. If the kernel-modules packages are needed they can
# be appended to IMAGE_INSTALL in a bbappend.
IMAGE_INSTALL += " \
    packagegroup-core-boot \
    packagegroup-core-ssh-openssh \
    qemu-system-i386 \
    xenguest-extern-guests \
    xenguest-manager \
    xenguest-network \
    "

# Build xen binary
EXTRA_IMAGEDEPENDS += "xen"

# Build xen-devicetree to produce a xen ready devicetree
EXTRA_IMAGEDEPENDS += "xen-devicetree"

REQUIRED_DISTRO_FEATURES += 'arm-autonomy-host'
REQUIRED_DISTRO_FEATURES += 'xen'
