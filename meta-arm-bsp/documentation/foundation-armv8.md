# Armv8-A Base Platform Support in meta-arm-platforms

## Howto Build and Run

### Configuration:
In the local.conf file, MACHINE should be set as follow:
MACHINE ?= "foundation-v8"

### Build:
```bash$ bitbake core-image-minimal```

### Run:
To Run the Fixed Virtual Platform simulation tool you must download "Armv8-A
Foundation Platform" from Arm developer (This might require the user to
register) from this address:
https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms
and install it on your host PC.

Fast Models Fixed Virtual Platforms (FVP) Reference Guide:
https://developer.arm.com/docs/100966/latest

Armv8‑A Foundation Platform User Guide:
https://developer.arm.com/docs/100961/latest/


Once done, do the following to build and run an image:
```bash$ bitbake core-image-minimal```
```bash$ export YOCTO_DEPLOY_IMGS_DIR="<yocto-build-dir/tmp/deploy/images/foundation-v8>"```
```bash$ cd <path-to-Foundation_Platformpkg-dir/models/Linux64_GCC-X.X/>```
```
bash$ ./Foundation_Platform --cores=4 --no-sve --gicv3 \
         --data=${YOCTO_DEPLOY_IMGS_DIR}/bl1-fvp.bin@0x0 \
         --data=${YOCTO_DEPLOY_IMGS_DIR}/Image@0x80080000 \
         --data=${YOCTO_DEPLOY_IMGS_DIR}/foundation-v8-gicv3-psci.dtb@0x83000000 \
         --block-device=${YOCTO_DEPLOY_IMGS_DIR}/core-image-minimal-foundation-armv8.disk.img \
```

If you have built a configuration without a ramdisk, you can use the following
command in U-boot to start Linux:
```VExpress64# booti 0x80080000 - 0x83000000```

## Devices supported in the kernel
- serial
- virtio disk
- network
- watchdog
- rtc

## Devices not supported or not functional
None
