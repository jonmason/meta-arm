# The TC3 model's libarmctmodel.so requests an executable stack. Clear that
# flag so current glibc can load it when the BSP runs its boot test.
require recipes-devtools/fvp/remove-execstack.inc
REMOVE_EXECSTACKS:x86-64 = "${FVPDIR}/models/${FVP_ARCH_DIR}*/libarmctmodel.so"
