# This files is added when DISTRO_FEATURES contains arm-autonomy-guest

# We need to have ipv4 activated
DISTRO_FEATURES_append = " ipv4"

# Build a xenguest type image
IMAGE_CLASSES += "image_types_xenguest"
IMAGE_FSTYPES += "xenguest"

# xenguest kernel extension to handle initramfs
KERNEL_CLASSES += "kernel-xenguest"
