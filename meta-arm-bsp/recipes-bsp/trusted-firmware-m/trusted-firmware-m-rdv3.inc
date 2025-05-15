DEPENDS += "python3-pyelftools-native python3-libclang-native python3-rich"
#DEPENDS += "python3-pyelftools-native python3-libclang-native python3-rich-native"

TFM_PLATFORM = "arm/rse/neoverse_rd/rdv3"
TFM_DEBUG = "1"
EXTRA_OECMAKE += "-DTFM_PLATFORM_VARIANT=0"
