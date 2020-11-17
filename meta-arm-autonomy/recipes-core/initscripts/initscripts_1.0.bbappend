do_install_append() {
    # We want to have checkroot.sh running before modutils.sh (06)
    update-rc.d -r ${D} -f checkroot.sh remove
    update-rc.d -r ${D} checkroot.sh start 05 S .
}
