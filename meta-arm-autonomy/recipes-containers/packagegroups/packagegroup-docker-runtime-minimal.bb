# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020 Arm Limited
#

SUMMARY = "Docker runtime minimal requirements"
DESCRIPTION = "The minimal set of packages required for running Docker"

inherit packagegroup

RDEPENDS:${PN} = "\
    docker-ce \
    docker-ce-contrib \
    kernel-module-xt-nat \
    kernel-module-xt-masquerade \
    kernel-module-xt-addrtype \
    kernel-module-xt-conntrack \
    kernel-module-xt-ipvs \
   "
