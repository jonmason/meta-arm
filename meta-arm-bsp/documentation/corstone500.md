# Corstone-500 Platform Support in meta-arm-bsp

## Howto Build and Run

### Configuration:
In the local.conf file, MACHINE should be set as follow:
MACHINE ?= "corstone500"
DISTRO ?= "poky-tiny"

Or set environment variables with that values:

MACHINE "corstone500"
DISTRO "poky-tiny"

### Build:
``bash$ bitbake arm-reference-image```

### Run:
To run the result in a Fixed Virtual Platform please get:
https://git.linaro.org/landing-teams/working/arm/model-scripts

and follow the instructions in the readme.txt file in that
repository.

