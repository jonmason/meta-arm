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

 - boot-wrapper-aarch64: provides PSCI support
 - U-Boot: v2021.07 - provides UEFI services
 - Linux kernel: linux-yocto-5.14
 - Linux kernel with PREEMPT\_RT support: linux-yocto-rt-5.14

Note that the Real-Time Linux kernel (PREEMPT\_RT) does not use the real-time
architectural extensions of the Armv8-R feature set.

High-Level Architecture
-----------------------

The diagram below shows the current boot flow:

    +---------------------------------------------------------------+
    |                         Linux kernel                          |
    +---------------------------------------------------------------+
               /|\                                     /|\
                |                                       |
                | UEFI services                         |
                |                         PSCI services |
               \|/                                      |
        +----------------+                              |     S-EL1
    ----|     U-Boot     |------------------------------|-----------
        +----------------+                              |     S-EL2
               /|\                                      |
                |                                       |
                |                                       |
                |                                       |
    +--------------------------------------------------\|/----------+
    |                        +----------------+ +----------------+  |
    |  boot-wrapper-aarch64  |  Device tree   | |  PSCI handler  |  |
    |                        +----------------+ +----------------+  |
    +---------------------------------------------------------------+


The firmware binary (generated as `linux-system.axf`) includes
boot-wrapper-aarch64, the flattened device tree and U-Boot. U-Boot is configured
to automatically detect a virtio block device and boot the UEFI payload at the
path `/efi/boot/bootaa64.efi`. Using the standard build, the first partition
contains a Grub image at this path, which boots the Linux kernel at `/Image` on
the same partition. The second partition of the image contains the Linux root
file system.

There is no EL3 or non-secure world in the Armv8-R AArch64 architecture, so the
reset vector starts boot-wrapper-aarch64 at S-EL2. Boot-wrapper-aarch64 is
compiled with the `--enable-keep-el` flag, which causes it to boot U-Boot at
S-EL2 too. U-Boot is compiled with the `CONFIG_ARMV8_SWITCH_TO_EL1` flag, which
causes it to switch to S-EL1 before booting Linux.

The bundled device tree is passed to U-Boot via register x0. U-Boot passes the
same device tree to Linux via the UEFI system table.

Power state management is provided by PSCI services in boot-wrapper-aarch64.
Linux accesses the PSCI handler via HVC calls to S-EL2. U-Boot has been patched
to prevent it from overriding the exception vector at S-EL2. The PSCI handler
memory region is added to a `/memreserve/` node in the device tree.

Please note that the final firmware architecture for the fvp-baser-aemv8r64 is
not yet stabilized. The patches in this layer are provided for development and
evaluation purposes only, and should not be used in production firmware.

Quick start: Howto Build and Run
--------------------------------

### Host environment setup
The following instructions have been tested on hosts running Ubuntu 18.04 and
Ubuntu 20.04.
Install the required packages for the build host:
https://docs.yoctoproject.org/singleindex.html#required-packages-for-the-build-host

Kas is a setup tool for bitbake based projects. The minimal supported version
is 2.6, install it like so:

    pip3 install --user kas

For more details on kas, see https://kas.readthedocs.io/.

To build the images for fvp-base machine, you also need to:

 - download the ``FVP_Base_AEMv8R_11.17_21.tgz`` image AEM V8-R FVP Installer
  (Linux) package from Arm's website:
  https://silver.arm.com/download/download.tm?pv=4865959&p=4029857. You need
   to have an account and be logged in to be able to download it
 - set absolute path to the ``FVP_Base_AEMv8R_11.17_21.tgz`` downloaded
   package in ``FVP_BASE_R_AEM_TARBALL_URI``
 - accept EULA in ``FVP_BASE_R_ARM_EULA_ACCEPT``


The variables should be set like so:

    FVP_BASE_R_AEM_TARBALL_URI="file:///absolute/path/to/FVP_Base_AEMv8R_11.17_21.tgz"
    FVP_BASE_R_ARM_EULA_ACCEPT="True"

**Note:** The host machine should have at least 50 GBytes of free disk space
for the next steps to work correctly.

### Fetch sources
To fetch and build the ongoing development of the software stack follow the
instructions on this document.

To fetch and build the version 1 (single core) find instructions at https://community.arm.com/developer/tools-software/oss-platforms/w/docs/633/release-1-single-core

To fetch and build the version 2 (linux smp) find instructions at https://community.arm.com/developer/tools-software/oss-platforms/w/docs/634/release-2---smp

Fetch the meta-arm repository into a build directory:

    mkdir -p ~/fvp-baser-aemv8r64-build
    cd ~/fvp-baser-aemv8r64-build
    git clone https://git.yoctoproject.org/git/meta-arm -b honister


### Build
Building with the standard Linux kernel:

    cd ~/fvp-baser-aemv8r64-build
    export FVP_BASE_R_AEM_TARBALL_URI="file:///absolute/path/to/FVP_Base_AEMv8R_11.17_21.tgz"
    export FVP_BASE_R_ARM_EULA_ACCEPT="True"
    kas build meta-arm/kas/fvp-baser-aemv8r64-bsp.yml

Building with the Real-Time Linux kernel (PREEMPT\_RT):

    cd ~/fvp-baser-aemv8r64-build
    export FVP_BASE_R_AEM_TARBALL_URI="file:///absolute/path/to/FVP_Base_AEMv8R_11.17_21.tgz"
    export FVP_BASE_R_ARM_EULA_ACCEPT="True"
    kas build meta-arm/kas/fvp-baser-aemv8r64-rt-bsp.yml

### Run
To run an image after the build is done with the standard Linux kernel:

    kas shell --keep-config-unchanged \
       meta-arm/kas/fvp-baser-aemv8r64-bsp.yml \
           --command "../layers/meta-arm/scripts/runfvp \
           --console "

To run an image after the build is done with the Real-Time Linux kernel
(PREEMPT\_RT):

    kas shell --keep-config-unchanged \
       meta-arm/kas/fvp-baser-aemv8r64-rt-bsp.yml \
           --command "../layers/meta-arm/scripts/runfvp \
           --console "

**Note:** The terminal console login is `root` without password.

To finish the fvp emulation, you need to close the telnet session:

 - Escape to telnet console with ``ctrl+]``.
 - Run ``quit`` to close the session.

### File sharing between host and fvp
It is possible to share a directory between the host machine and the fvp using
the virtio P9 device component included in the kernel. To do so, create a
directory to be mounted from the host machine:

    mkdir /path/to/host-mount-dir

Then, add the following parameter containing the path to the directory when
launching the model:

    --parameter 'bp.virtiop9device.root_path=/path/to/host-mount-dir'

e.g. for the standard Linux kernel:

    kas shell --keep-config-unchanged \
       meta-arm/kas/fvp-baser-aemv8r64-bsp.yml \
           --command "../layers/meta-arm/scripts/runfvp \
           --console --parameter
           'bp.virtiop9device.root_path=/path/to/host-mount-dir'"

Once you are logged into the fvp, the host directory can be mounted in a
directory on the model using the following command:

    mount -t 9p -o trans=virtio,version=9p2000.L FM /path/to/fvp-mount-dir

Devices supported in the kernel
-------------------------------

- serial
- virtio 9p
- virtio disk
- virtio network
- watchdog
- rtc

Known Issues and Limitations
----------------------------

- Only PSCI CPU\_ON and CPU\_OFF functions are supported
- Linux kernel does not support booting from secure EL2 on Armv8-R AArch64
- Linux KVM does not support Armv8-R AArch64
- Device DMA memory cache-coherence issue: the FVP cache_state_modelled
  parameter will affect the cache coherence behavior of peripherals’ DMA. When
  users set cache_state_modelled=1, they also have to set
  cci400.force_on_from_start=1 to force the FVP to enable snooping on upstream
  ports.

Change Log
----------

- Added U-Boot v2021.07 for UEFI support.
- Updated boot-wrapper-aarch64 revision and added support for booting U-Boot.
- Included boot-wrapper-aarch64 PSCI services in /memreserve/ region.
- Fixed the counter frequency initialization in boot-wrapper-aarch64.
- Configured the FVP to use the default RAM size of 4 Gb
- Fixed PL011 and SP805 register sizes in the device tree.
- Added virtio_net User Networking mode by default and removed instructions
  about tap networking setup.
- Updated Linux kernel version from 5.10 to 5.14 for both standard and
  Real-Time (PREEMPT\_RT) builds.
- Enabled SMP support via boot-wrapper-aarch64 providing the PSCI CPU_ON and
  CPU_OFF functions.
- Introduced Armv8-R64 compiler flags.
- Added Linux PREEMPT\_RT support via linux-yocto-rt-5.10.
- Added support for file sharing with the host machine using Virtio P9.
- Added support for runfvp.
- Added performance event support (PMU) in the Linux device tree.
- Introduced the fvp-baser-aemv8r64 machine and its BSP composed of
  boot-wrapper-aarch64 and linux-yocto-5.10 supporting serial, virtio disk,
  virtio network, watchdog and rtc.
