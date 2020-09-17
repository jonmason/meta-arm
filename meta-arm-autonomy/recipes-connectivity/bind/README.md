For now, arm-autonomy-host-image-minimal installs the dhcp-server package and
the dchp-4.4.2 depends on bind 9.11 which recipe was copied from oe-core tree
https://git.openembedded.org/openembedded-core/tree/meta/recipes-connectivity/bind?id=087e4fafeef82cfd3d71402d6b200fe831f48697
since it got removed in the https://git.openembedded.org/openembedded-core/commit/meta/recipes-connectivity?id=29949cd7cf3a660fb3bcf251f5127a4cdb2804ec patch.
