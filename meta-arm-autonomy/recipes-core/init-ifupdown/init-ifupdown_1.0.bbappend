# Add support for interface configuration via interfaces.d directory. This
# feature can be used by other packages to add network interface
# configuration by adding network network interface configuration file under
# interfaces.d directory.

do_install_append() {
    # Add scan of interfaces.d to interfaces file
    cp -f ${WORKDIR}/interfaces ${WORKDIR}/interfaces.subdir
    echo "source-directory ${sysconfdir}/network/interfaces.d/" \
        >> ${WORKDIR}/interfaces.subdir

    # Create interfaces.d script in case nobody is adding a script
    # so that there is no error about non existing directory
    install -d -m 755 ${D}${sysconfdir}/network/interfaces.d

    # Install our file instead of the original one
    install -m 644 interfaces.subdir ${D}${sysconfdir}/network/interfaces
}
