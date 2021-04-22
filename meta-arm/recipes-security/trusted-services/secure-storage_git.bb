SUMMARY = "Secure storage secure partition"

require sp.inc

TS_DEPLOYMENT = "${S}/deployments/secure-storage/shim"

do_install () {
    install -d -m 755 ${D}/firmware
    install -m 0644 "${B}/secure-storage.bin" "${D}/firmware/secure-storage.bin"
    install -m 0644 "${S}/deployments/secure-storage/shim/secure-storage.dts" \
        "${D}/firmware/secure-storage.dts"
}

FILES_${PN} = "/firmware/secure-storage.bin /firmware/secure-storage.dts"
