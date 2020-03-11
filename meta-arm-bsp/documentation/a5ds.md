# Cortex-A5 DesignStart A5DS Platform Support in meta-arm-platforms

## Howto Build and Run

### Configuration:
In the local.conf file, MACHINE should be set as follow:
MACHINE ?= "a5ds"
DISTRO ?= "iota-tiny"

Or set environment variables with that values:

MACHINE "a5ds"
DISTRO "iota-tiny"

### Build:
``bash$ bitbake iota-tiny-image```

### Run:
To run the result in a Fixed Virtual Platform please get:
https://git.linaro.org/landing-teams/working/arm/model-scripts

and follow the instructions in the readme.txt file in that
repository.

