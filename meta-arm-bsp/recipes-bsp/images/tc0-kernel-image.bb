# SPDX-License-Identifier: Apache-2.0
#
# Copyright (c) 2020 Arm Limited
#

SUMARY = "Total Compute Images"
DESCRIPTION = "Build all the images required for Total Compute platform"
LICENSE = "Apache-2.0"

# The last image to be built is trusted-firmware-a
DEPENDS += " trusted-firmware-a"
