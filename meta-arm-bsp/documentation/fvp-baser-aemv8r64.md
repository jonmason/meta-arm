Armv8-R AArch64 AEM FVP Support in meta-arm-bsp
===============================================

Overview
--------

Fixed Virtual Platforms (FVP) are complete simulations of an Arm system,
including processor, memory and peripherals. These are set out in a
"programmer's view", which gives you a comprehensive model on which to build
and test your software.

The Armv8-R AEM FVP is a free of charge Armv8-R Fixed Virtual Platform. It
supports the latest Armv8-R feature set.

This BSP implements a reference stack for the AArch64 support in the R-class
first announced with the Cortex-R82 processor:
https://developer.arm.com/ip-products/processors/cortex-r/cortex-r82

Fast Models Fixed Virtual Platforms (FVP) Reference Guide:
https://developer.arm.com/docs/100966/latest


BSP Support
-----------

The fvp-baser-aemv8r64 Yocto MACHINE supports the following BSP components,
where either a standard or Real-Time Linux kernel (PREEMPT\_RT) can be built
and run:

 - boot-wrapper-aarch64
 - Linux kernel: linux-yocto-5.10
 - Linux kernel with PREEMPT\_RT support: linux-yocto-rt-5.10

Note that the Real-Time Linux kernel (PREEMPT\_RT) does not use the real-time
architectural extensions of the Armv8-R feature set.


Quick start: Howto Build and Run
--------------------------------

### Host environment setup
The following instructions have been tested on hosts running Ubuntu 18.04 and
Ubuntu 20.04.
Install the required packages for the build host:
https://docs.yoctoproject.org/singleindex.html#required-packages-for-the-build-host

Install the kas setup tool for bitbake based projects:

    pip3 install --user kas

For more details on kas, see https://kas.readthedocs.io/.

**Note:** The host machine should have at least 50 GBytes of free disk space
for the next steps to work correctly.

### Fetch sources
Fetch the meta-arm repository into a build directory:

    mkdir -p ~/fvp-baser-aemv8r64-build
    cd ~/fvp-baser-aemv8r64-build
    git clone https://git.yoctoproject.org/git/meta-arm


### Build
Building with the standard Linux kernel:

    cd ~/fvp-baser-aemv8r64-build
    kas build meta-arm/kas/fvp-baser-aemv8r64-bsp.yml

Building with the Real-Time Linux kernel (PREEMPT\_RT):

    cd ~/fvp-baser-aemv8r64-build
    kas build meta-arm/kas/fvp-baser-aemv8r64-rt-bsp.yml

### Networking
To enable networking on the FVP via a host network interface, you will need to
install the following package(s):

**Ubuntu 18.04:**

    sudo apt-get install libvirt-bin

**Ubuntu 20.04:**

    sudo apt-get install libvirt-dev libvirt-daemon qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils

Once that is installed for your OS version, setup tap0 using the following
commands:

    sudo virsh net-start default
    sudo ip tuntap add dev tap0 mode tap user $(whoami)
    sudo ifconfig tap0 0.0.0.0 promisc up
    sudo brctl addif virbr0 tap0

To clean up the tap0 interface on the host use the following commands:

    sudo brctl delif virbr0 tap0
    sudo ip link set virbr0 down
    sudo brctl delbr virbr0
    sudo virsh net-destroy default
    sudo ip link delete tap0

### Run
To Run the Fixed Virtual Platform simulation tool you must download "Armv8-R
AEM FVP" from Arm developer (This might require the user to register) from this
address:
https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms/arm-ecosystem-models
and install it on your host PC.

To run an image after the build is done:

    export YOCTO_DEPLOY_IMGS_DIR="~/fvp-baser-aemv8r64-bsp/build/tmp/deploy/images/fvp-baser-aemv8r64/"
    cd <path-to-AEMv8R_base_pkg>/models/Linux64_GCC-6.4/
    ./FVP_BaseR_AEMv8R \
        -C bp.dram_metadata.init_value=0 \
        -C bp.dram_metadata.is_enabled=true \
        -C bp.dram_size=8 \
        -C bp.exclusive_monitor.monitor_access_level=1 \
        -C bp.pl011_uart0.unbuffered_output=1 \
        -C bp.pl011_uart0.untimed_fifos=true \
        -C bp.refcounter.non_arch_start_at_default=1 \
        -C bp.smsc_91c111.enabled=0 \
        -C bp.ve_sysregs.mmbSiteDefault=0 \
        -C cache_state_modelled=true \
        -C cluster0.gicv3.cpuintf-mmap-access-level=2 \
        -C cluster0.gicv3.SRE-enable-action-on-mmap=2 \
        -C cluster0.gicv3.SRE-EL2-enable-RAO=1 \
        -C cluster0.gicv3.extended-interrupt-range-support=1 \
        -C cluster0.has_aarch64=1 \
        -C cluster0.NUM_CORES=4 \
        -C cluster0.stage12_tlb_size=512 \
        -C gic_distributor.GICD_CTLR-DS-1-means-secure-only=1 \
        -C gic_distributor.GITS_BASER0-type=1 \
        -C gic_distributor.ITS-count=1 \
        -C gic_distributor.ITS-hardware-collection-count=1 \
        -C gic_distributor.has-two-security-states=0 \
        -C pctl.startup=0.0.0.* \
        -C bp.virtio_net.enabled=1 \
        -C cache_state_modelled=0 \
        -C bp.vis.rate_limit-enable=0 \
        -C bp.virtio_net.hostbridge.interfaceName=tap0 \
        -a cluster0*=${YOCTO_DEPLOY_IMGS_DIR}/linux-system.axf \
        -C bp.virtioblockdevice.image_path=${YOCTO_DEPLOY_IMGS_DIR}/core-image-minimal-fvp-baser-aemv8r64.wic

**Note:** The terminal console login is `root` without password.


Devices supported in the kernel
-------------------------------

- serial
- virtio disk
- virtio network
- watchdog
- rtc


Devices not supported or not functional
---------------------------------------

- Only one CPU since SMP is not functional in boot-wrapper-aarch64 yet

