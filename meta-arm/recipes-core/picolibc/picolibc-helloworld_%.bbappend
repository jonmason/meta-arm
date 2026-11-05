COMPATIBLE_MACHINE = "qemuarm-m3"
PICOLIBC_LINKERSCRIPT:qemuarm-m3 = "arm.ld"

inherit baremetal-testimage

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append:qemuarm-m3 = " file://mps2-uart.c"

# Send the test result over the MPS2 UART; semihosting is only used to exit.
do_compile:qemuarm-m3() {
    ${CC} ${CFLAGS} -ffile-prefix-map=${UNPACKDIR}=. ${LDFLAGS} \
        -T${S}/hello-world/${PICOLIBC_LINKERSCRIPT} \
        -specs=picolibc.specs --oslib=semihost -o ${BAREMETAL_BINNAME}.elf \
        ${UNPACKDIR}/mps2-uart.c
    ${OBJCOPY} -O binary ${BAREMETAL_BINNAME}.elf ${BAREMETAL_BINNAME}.bin
}

TESTIMAGE_EXPECTED_OUTPUT = "hello, world"
TEST_QEMUBOOT_TIMEOUT = "30"
