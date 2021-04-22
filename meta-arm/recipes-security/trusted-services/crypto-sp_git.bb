SUMMARY = "crypto-sp secure partition"

require sp.inc

TS_DEPLOYMENT = "${S}/deployments/crypto/shim/"

do_install () {
    install -d -m 755 ${D}/firmware
    install -m 0644 "${B}/crypto-sp.bin" "${D}/firmware/crypto-sp.bin"
    install -m 0644 "${S}/deployments/crypto/shim/crypto.dts" \
        "${D}/firmware/crypto.dts"
}

FILES_${PN} = "/firmware/crypto-sp.bin /firmware/crypto.dts"
