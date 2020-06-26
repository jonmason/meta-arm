# Gem5 Arm64 Platform Support in meta-arm-platforms

## Howto Build and Run

### Configuration:
In the local.conf file, MACHINE should be set as follow:
MACHINE ?= "gem5-arm64"

### Build:
```bash$ bitbake core-image-minimal```


### Run:
After compilation of an image, you can execute it using the compiled gem5
with the followin command:
```./tmp/deploy/tools/start-gem5.sh```

You can modify the script to change the command line options of gem5.

## Devices supported in the kernel
- serial

### Untested:
- pci
- sata
- ide


## Devices not supported or not functional
