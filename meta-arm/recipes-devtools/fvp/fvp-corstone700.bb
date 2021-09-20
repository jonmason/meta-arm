require fvp-ecosystem.inc

MODEL = "Corstone-700"
MODEL_CODE = "FVP_Corstone_700"
PV = "11.10.47"

# Temporary SRC_URI as the URL structure is unconventional
SRC_URI = "https://developer.arm.com/-/media/Arm%20Developer%20Community/Downloads/OSS/FVP/${MODEL}/Corstone-700-updated-11-10-47/${MODEL_CODE}_${PV_URL}.tgz;subdir=${BP}"
SRC_URI[sha256sum] = "255207771864edeca2610958811d30e458c03a2db01950355a455513bad782ec"
