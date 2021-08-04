# This class is to be inherited by image recipes that want to build and install
# an alternate kernel (set via PREFERRED_PROVIDER_alternate/kernel).
#
# It is mandatory to also set the KERNEL_PACKAGE_NAME for the alternate kernel
# recipe via KERNEL_PACKAGE_NAME:pn-${PREFERRED_PROVIDER_alternate/kernel} and
# its value needs to be different from "kernel" since this is the default set
# for PREFERRED_PROVIDER_virtual/kernel.
#
# An example of these settings can be found at meta-arm-autonomy/dynamic-layers/meta-arm-bsp/conf/machine/n1sdp-extra-settings.inc
#
# When building and installing an alternate kernel, the kernel-modules packages
# for both virtual/kernel and alternate/kernel will be installed.

PREFERRED_PROVIDER_alternate/kernel ??= ""

python () {
    alternate_kernel = d.getVar('PREFERRED_PROVIDER_alternate/kernel')
    if alternate_kernel:
        alternate_kernel_pkg_name = d.getVar('KERNEL_PACKAGE_NAME:pn-%s' % alternate_kernel)
        if alternate_kernel_pkg_name:
            d.appendVar('EXTRA_IMAGEDEPENDS', ' ' + alternate_kernel)
            d.appendVar('IMAGE_INSTALL', ' kernel-modules')
            d.appendVar('IMAGE_INSTALL', ' ' + alternate_kernel_pkg_name + '-modules')
        else:
            raise bb.parse.SkipRecipe("No KERNEL_PACKAGE_NAME:pn-%s set" % alternate_kernel )
}
