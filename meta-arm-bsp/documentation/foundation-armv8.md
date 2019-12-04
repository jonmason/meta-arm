# Armv8-A Base Platform Support in meta-arm-platforms

## Howto Build and Run

### Configuration:
In the local.conf file, MACHINE should be set as follow:
MACHINE ?= "foundation-v8"

### Build:
```bash$ bitbake core-image-minimal```

### Run:
The layer provides a recipe to install the Armv8-A Foundation Platform in your
environment. You must download Armv8-A Foundation Platform from Arm developer
(This might require the user to register) from this address:
https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms
and put the downloaded tar file in 'downloads/licensed/silver.arm.com/'
directory of your project (or of your Pre-Mirror if you have one).

Once done, do the following to build and run an image:
```bash$ bitbake core-image-minimal```
```bash$ ./tmp/deploy/tools/start-foundation-armv8.sh```

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
