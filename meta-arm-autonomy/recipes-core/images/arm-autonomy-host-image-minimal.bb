# Recipe to create a minimal Arm Autonomy stack host image

DESCRIPTION = "Arm Autonomy stack host minimal image"

inherit core-image

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# The ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS variable can be used to include in the
# image one or several xenguest images.
# The list must be space separated and each entry must have the following
# format: URL[;guestname=NAME]
#  - URL can be the full path to a file or a Yocto compatible SRC_URI url
#  - guestname=NAME can be used to specify the name of the guest. If not
#    specified the basename of the file (without .xenguest extension) is used.
#  Here are examples of values:
#  /home/mydir/myguest.xenguest;guestname=guest1
#  http://www.url.com/testguest.xenguest
#
#  If you are using the output of an other Yocto project, you should use the
#  full path syntax instead of the Yocto SRC_URI to be able to use the
#  symlink version of your image (as the real file has a new name on each
#  build as it includes the date). You must not use SRC_URI type file:// as
#  it will try to include the symlink and not the destination file which will
#  be detected by the recipe and output an error 'Guest file is a symlink'.
#
#  Guests can also be added using a bbapend to this recipe by adding entries
#  to SRC_URI with parameter ;guestname=NAME to specify the destination
#  guestname. The parameter guestname must be present as it is used to detect
#  guests to be added
ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS ??= ""

# Includes minimal set required to start and manage guest. The xen specific
# modules are not explicitly included as they are built as part of the kernel
# image for performance reasons. It doesn't include all kernel modules to
# reduce the image size. If the kernel-modules packages are needed they can
# be appended to IMAGE_INSTALL in a bbappend.
IMAGE_INSTALL += " \
    packagegroup-core-boot \
    packagegroup-core-ssh-openssh \
    qemu-xen \
    xenguest-manager \
    xenguest-network-bridge \
    "

# Build xen binary
EXTRA_IMAGEDEPENDS += "xen"

# Build xen-devicetree to produce a xen ready devicetree
EXTRA_IMAGEDEPENDS += "xen-devicetree"

python __anonymous() {
    if bb.utils.contains('DISTRO_FEATURES', 'arm-autonomy-host', False, True, d):
        raise bb.parse.SkipRecipe("DISTRO_FEATURES does not contain 'arm-autonomy-host'")

    if bb.utils.contains('DISTRO_FEATURES', 'xen', False, True, d):
        raise bb.parse.SkipRecipe("DISTRO_FEATURES does not contain 'xen'")

    # Check in ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS for extra guests and add them
    # to SRC_URI with xenguest parameter if not set
    guestlist = d.getVar('ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS')
    if guestlist:
        for guest in guestlist.split():
            # If the user just specified a file instead of file://FILE, add
            # the file:// prefix
            if guest.startswith('/'):
                guestfile = ''
                guestname = ''
                if ';guestname=' in guest:
                    # user specified a guestname
                    guestname = guest.split(';guestname=')[1]
                    guestfile = guest.split(';guestname=')[0]
                else:
                    # no guestname so use the basename
                    guestname = os.path.basename(guest)
                    guestfile = guest
                # in case we have a link we need the destination
                guestfile = os.path.realpath(guestfile)

                # make sure the file exist to give a meaningfull error
                if not os.path.exists(guestfile):
                    raise bb.parse.SkipRecipe("ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS entry does not exist: " + guest)

                # In case the file is a symlink make sure we use the destination
                d.appendVar('SRC_URI',  ' file://' + guestfile + ';guestname=' + guestname)
            else:
                # we have a Yocto URL
                try:
                    _, _, path, _, _, parm = bb.fetch.decodeurl(guest)
                    # force guestname param in if not already there
                    if not 'guestname' in parm:
                        guest  += ';guestname=' + os.path.basename(path)
                    d.appendVar('SRC_URI', ' ' + guest)
                except:
                    raise bb.parse.SkipRecipe("ARM_AUTONOMY_HOST_IMAGE_EXTERN_GUESTS contains an invalid entry: " + guest)
}

python add_extern_guests () {
    # Destination directory on the rootfs
    guestdir = d.getVar('IMAGE_ROOTFS') + d.getVar('datadir') + '/guests'

    # Parse SRC_URI for files with ;guestname= parameter
    src_uri = d.getVar('SRC_URI')
    for entry in src_uri.split():
        _, _, path, _, _, parm = bb.fetch.decodeurl(entry)
        if 'guestname' in parm:
            if os.path.islink(path):
                bb.fatal("Guest file is a symlink: " + path)
            bb.utils.mkdirhier(guestdir)
            dstname = parm['guestname']
            # Add file extension if not there
            if not dstname.endswith('.xenguest'):
                dstname += '.xenguest'
            if not bb.utils.copyfile(path, guestdir + '/' + dstname):
                bb.fatal("Fail to copy Guest file " + path)
}

IMAGE_PREPROCESS_COMMAND += "add_extern_guests; "

